#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>

#include "schemaversion.h"

SchemaVersion::SchemaVersion()
{
    m_version = 0;
    m_tableName = QString("schema_version");
}

SchemaVersion::~SchemaVersion()
{

}

QString SchemaVersion::tableName() const
{
    return m_tableName;
}

void SchemaVersion::setTableName(const QString &tableName)
{
    m_tableName = tableName;
}

float SchemaVersion::version() const
{
    return m_version;
}

void SchemaVersion::setVersion(float version)
{
    m_version = version;
}

QString SchemaVersion::description() const
{
    return m_description;
}

void SchemaVersion::setDescription(const QString &description)
{
    m_description = description;
}

int SchemaVersion::executionTime() const
{
    return m_executionTime;
}

void SchemaVersion::setExecutionTime(int executionTime)
{
    m_executionTime = executionTime;
}

QString SchemaVersion::script() const
{
    return m_script;
}

void SchemaVersion::setScript(const QString &script)
{
    m_script = script;
}

bool SchemaVersion::createVersionTable()
{
    QSqlDatabase::database().transaction();
    QSqlQuery query;

    bool executed;
    executed = query.exec("CREATE TABLE "+tableName()+" ("
                          "   version FLOAT NULL, "
                          "   description VARCHAR(200) NULL,"
                          "   script VARCHAR(10000) NULL,"
                          "   executed_on VARCHAR(25) NULL,"
                          "   executed_time INT NULL"
                          ");");

    if (executed) {
        QSqlDatabase::database().commit();
    } else {
        QSqlDatabase::database().rollback();
        setLastError(query.lastError().text());
    }

    return executed;
}

void SchemaVersion::loadCurrentVersion()
{
    QSqlQuery query;
    query.exec("select * from " + tableName());

    if (query.size() == 0)
        return;

    if (query.last()) {
        m_version = query.value("version").toFloat();
        m_description = query.value("description").toString();
        m_script = query.value("script").toString();
        m_executedOn = query.value("executed_on").toDateTime();
        m_executionTime = query.value("executed_time").toInt();
    }
}

QStringList SchemaVersion::makeSQLFormat(const QSqlQuery &q)
{
    QStringList list;
    list << "Parameters: ";

    QMapIterator<QString, QVariant> i(q.boundValues());
    while (i.hasNext()) {
        i.next();
        list << QString("%1 = %2").arg(i.key().toUtf8().data())
                                  .arg(i.value().toString().toUtf8().data());
    }

    list << "---------------------";
    list << q.lastQuery();
    return list;
}

QStringList& SchemaVersion::lastSqlInsert()
{
    return m_lastSqlInsert;
}

void SchemaVersion::setLastSqlInsert(const QStringList &lastSqlInsert)
{
    m_lastSqlInsert = lastSqlInsert;
}

QString SchemaVersion::lastError() const
{
    return m_lastError;
}

void SchemaVersion::setLastError(const QString &lastError)
{
    m_lastError = lastError;
}


bool SchemaVersion::checkVersionTable()
{
    if (!QSqlDatabase::database().tables().contains(tableName()))
        return createVersionTable();
    
    loadCurrentVersion();
    return true;
}

bool SchemaVersion::writeDbChanges(Migration &migration)
{
    QSqlQuery query;
    query.prepare("insert into " + tableName() +
                  " (version, description, script, executed_on) "
                  "values "
                  " (:v , :d, :s, :h)");
    query.bindValue(0, migration.version());
    query.bindValue(1, migration.description());
    query.bindValue(2, migration.SQL());
    query.bindValue(3, QDateTime::currentDateTime().toString());

    if (!query.exec()) {
        setLastError("Erro on saving log changes: " + query.lastError().text());
        return false;
    }

    setLastSqlInsert(makeSQLFormat(query));
    return true;
}










