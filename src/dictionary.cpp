#include <QDialog>
#include <QApplication>
#include <QtGlobal>

#include "connection.h"
#include "dictionary.h"

Dictionary::Dictionary()
{

}

Dictionary::~Dictionary()
{

}

void Dictionary::Migrate(const QString xmlPath)
{
    loadTablesFromFile(xmlPath);
    compareTables();
}

void Dictionary::compareTables()
{
    dlg = new MigrationProgress();
    dlg->setWindowFlags( Qt::CustomizeWindowHint );
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
                QSqlDatabase::database().commit();
                qDebug() << "[Criando tabela " << table.name() << "]";
                dlg->setStatus("Criando tabela: "+table.name(),"red");
                CreatedTables++;
            }
            else
            {
                QSqlDatabase::database().rollback();
                qDebug() << "[Erro ao criar tablela: " << table.name() << "Erro: " << QSqlDatabase::database().lastError().text() << "]";
            }
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

    for (int i = 0; i != table.fields.count(); i++)
    {
        Fields field = table.fields.at(i);
        SQL += field.name() + " ";

        switch (field.type())
        {
            case ftInteger:
                SQL += "INT ";
                break;

            case ftVarchar:
                SQL += "VARCHAR(" + QString::number(field.size()) + ") ";
                break;

            case ftBoolean:
                SQL += "BOOLEAN ";
                break;

            case ftDateTime:
                SQL += "DATETIME ";
                break;

            case ftFloat:
                SQL += "FLOAT ";
                break;

            default:
                SQL += "VARCHAR(" + QString::number(field.size()) + ") ";
                break;
        }

        SQL +=  "NULL ";

        field.defaultValue() == "" ? SQL += "NULL" : SQL += field.defaultValue().toString();

        SQL += ",";
    }

    for (int i = 0; i != table.fields.count(); i++)
    {
        Fields field = table.fields.at(i);

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
