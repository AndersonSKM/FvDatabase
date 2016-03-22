#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>

#include "schemaversion.h"

SchemaVersion::SchemaVersion()
{
    m_version = 0;
    m_tableName = QString("SCHEMA_VERSION");
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
                          "   script VARCHAR(1000) NULL,"
                          "   executed_on VARCHAR(15) NULL,"
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
    query.prepare("insert into :tableName "
                  " (version, description, script, datehour) "
                  "values "
                  " (:v , :d, :s, :h)");
    query.bindValue(0, tableName());
    query.bindValue(1, migration.version());
    query.bindValue(2, migration.description());
    query.bindValue(3, migration.SQL());
    query.bindValue(4, QDateTime::currentDateTime().toString());

    if (!query.exec()) {
        setLastError(query.lastError().text());
        return false;
    }

    return true;
}










