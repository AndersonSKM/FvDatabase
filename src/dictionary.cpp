#include "connection.h"
#include "dictionary.h"

void Dictionary::Migrate(const QString xmlPath)
{
    loadTablesFromFile(xmlPath);

    compareTables();
}

void Dictionary::compareTables()
{
    QSqlQuery query( Database::DB() );

    for (int i = 0; i != Tables.count(); i++)
    {
        Table table = Tables.at(i);
        if ( !Database::DB().tables().contains( table.name() ) )
        {
            //Database::transaction();
            if ( query.exec( generateSQL(table) ) )
            {
                //Database::commit();
                qDebug() << "[Criando tabela " << table.name() << "]";
            }
            else
               qDebug() << "[Erro ao criar tablela: " << table.name() << "Erro: " << Database::DB().lastError().text() << "]";
        }
    }
}

void Dictionary::loadTablesFromFile(const QString &filePath)
{
    DictXML dici;
    dici.setFilePath(filePath);

    QDomNodeList tablesNodes = dici.InitXML(dici.filePath,"Table");

    for (int i = 0; i != tablesNodes.count(); i++)
    {
        QDomNode tableNode = tablesNodes.at(i);
        if (tableNode.isElement())
        {
            QDomElement tableElement = tableNode.toElement();
            Tables.append( dici.LoadTable(tableElement.attribute("Name").toUpper()) );
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

bool Dictionary::createTables()
{
    Database::transaction();
    qDebug() << "[Iniciando criacao de tabelas]";

    QSqlQuery *query = new QSqlQuery;

    for (int i = 0; i != Tables.count(); i++)
    {
        Table table = Tables.at(i);
        if (Database::DB().tables().contains(table.name()))
        {
            query->exec(generateSQL(table));
            qDebug() << "[Criando tabela "+table.name()+"]";
        }
    }

    Database::commit();
    qDebug() << "[Finalizado criacao de tabelas]";
return true;
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
