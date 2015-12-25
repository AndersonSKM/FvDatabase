#include <QDialog>
#include <QApplication>
#include <QtGlobal>

#include "connection.h"
#include "dictionary.h"

Dictionary::Dictionary()
{
    m_progressVisible = true;
}

Dictionary::~Dictionary()
{

}

void Dictionary::Migrate(const QString xmlPath)
{
    loadTablesFromFile(xmlPath);
    compareTables();
}

void Dictionary::setProgressVisible(bool visible)
{
    m_progressVisible = visible;
}

bool Dictionary::progressVisible(void)
{
    return m_progressVisible;
}

void Dictionary::compareTables()
{
    dlg = new MigrationProgress();
    dlg->setWindowFlags( Qt::CustomizeWindowHint );

    if (progressVisible())
        dlg->show();

    QSqlQuery query;

    int CreatedTables = 0;
    int progress = round(Tables.count()/100);
    int value = 0;

    dlg->setMaximum(progress*Tables.count());

    qDebug() << "[Verificando Lista de Tabelas....]";

    for (int i = 0; i != Tables.count(); i++)
    {   
        Table table = Tables.at(i);

        dlg->setStatus("Verificando tabela: "+table.name());
        dlg->update();

        if ( !QSqlDatabase::database().tables().contains( table.name() ) )
        {
            QSqlDatabase::database().transaction();

            if (query.exec(generateSQL(table)))
            { 
                qDebug() << "[Criando tabela " << table.name() << "]";
                dlg->setStatus("Criando tabela: "+table.name(),"red");
                CreatedTables++;
            }
            else
                qDebug() << "[Erro ao criar tablela: " << table.name() << "Erro: " << query.lastError().text() << "]";

            QSqlDatabase::database().commit();
        }
        else
        {
            compareFields(table);
        }

        dlg->setProgress(value += progress);

        QApplication::processEvents();
        dlg->update();
    }
    qDebug() << "[Finalizando Verificação de Tabelas....]";
    qDebug() << "[Tabelas verificadas: " << Tables.count() << "]";
    qDebug() << "[Tabelas criadas: " << CreatedTables << "]";

    delete dlg;
}

void Dictionary::compareFields(Table &table)
{
    Fields field;
    foreach (field, table.fields)
    {
        if (!columnExists(table.name(), field.name()))
        {
            dlg->setStatus("Alterando tabela: "+table.name(),"red");
            QSqlQuery q;
            if (!q.exec(generateAddColumnSQL(table.name(),field)) )
            {
                qDebug() << "Erro ao adicionar coluna: " << field.name()
                         << ":" << q.lastError().text()
                         << " : " << q.lastQuery();
            }
        }
    }
}

bool Dictionary::columnExists(QString tableName, QString columnName)
{
    /* Verifica se a coluna existe na tabela */
    QSqlQuery q;
    q.prepare("SELECT * "
              "FROM information_schema.columns "
              "WHERE table_schema = :dbName "
              "  AND table_name   = :tbName"
              "  AND column_name  = :colName");
    q.bindValue(0,QSqlDatabase::database().databaseName());
    q.bindValue(1,tableName);
    q.bindValue(2,columnName);
    q.exec();

    if (q.next())
        return true;

    return false;
}

QString Dictionary::generateAddColumnSQL(QString tableName, Fields field)
{
    QString SQL = "ALTER TABLE " + tableName +
                  " ADD "+ field.toSQL();
    return SQL;
}

void Dictionary::loadTablesFromFile(const QString &filePath)
{
    DictXML dici;
    dici.setFilePath(filePath);

    QDomDocument doc = dici.InitXML(dici.filePath);
    QDomNodeList root = doc.elementsByTagName("Table");

    qDebug() << "[Carregando tabelas do arquivo " << filePath << "]";

    for (int i = 0; i != root.count(); i++)
    {
        QDomNode tableNode = root.at(i);
        if (tableNode.isElement())
        {
            QDomElement tableElement = tableNode.toElement();
            Tables.append( dici.LoadTable(tableElement.attribute("Name")) );
        }
    }
}

QString Dictionary::generateSQL(Table &table)
{
    //Gera o SQL create da tabela passada como parametro *
    QString SQL;
    SQL += "CREATE TABLE " + table.name() + "( ";

    for (auto i = table.fields.begin(); i != table.fields.end(); ++i)
    {
        Fields &field = *i;
        SQL += field.toSQL();
        SQL += ",";
    }

    for (auto i = table.fields.begin(); i != table.fields.end(); ++i)
    {
        Fields &field = *i;
        if ( field.isPrimaryKey() )
            SQL += "PRIMARY KEY(" + field.name() + ")";
    }

    SQL += ");";

    return SQL;
}

// ** Table class implementation **

void Table::setName(QString name)
{
    t_name = name;
}

QString Table::name(void)
{
    return t_name;
}

// ** Fields class implementation **

Fields::Fields(QString name, DataTypes type, int size, bool pk, QVariant def)
{
    f_name = name;
    f_type = type;
    f_size = size;
    f_primaryKey = pk;
    f_defaultValue = def;
}

Fields::~Fields()
{

}

QString Fields::toSQL(void)
{
    QString SQL;
    SQL += name();
    SQL += " " + typeToSQL(type());
    SQL += size() != 0 ? "(" + QString::number(size()) + ")" : "";
    SQL += " NULL ";

    if (! (defaultValue() == "")) {
        SQL += "DEFAULT ";

        if (type() == ftVarchar)
            SQL += "'" + defaultValue().toString() + "'";
        else
            SQL += defaultValue().toString();
    } else {
        SQL += "NULL";
    }

    return SQL;
}

QString Fields::typeToSQL(DataTypes type)
{
    QString SQL;

    switch (type)
    {
        case ftInteger:
            SQL += "INT";
            break;

        case ftVarchar:
            SQL += "VARCHAR";
            break;

        case ftBoolean:
            SQL += "BOOLEAN";
            break;

        case ftDateTime:
            SQL += "DATETIME";
            break;

        case ftFloat:
            SQL += "FLOAT";
            break;

        default:
            SQL += "VARCHAR";
            break;
    }

    return SQL;
}

void Fields::setName(QString name)
{
    f_name = name;
}

void Fields::setType(DataTypes type)
{
    f_type = type;
}

void Fields::setSize(int size)
{
    f_size = size;
}

void Fields::setPrimaryKey(bool pk)
{
    f_primaryKey = pk;
}

void Fields::setDefaultValue(QVariant def)
{
    f_defaultValue = def;
}

QString Fields::name(void)
{
    return f_name;
}

DataTypes Fields::type(void)
{
    return f_type;
}

int Fields::size(void)
{
    return f_size;
}

bool Fields::isPrimaryKey(void)
{
    return f_primaryKey;
}

QVariant Fields::defaultValue(void)
{
    return f_defaultValue;
}
