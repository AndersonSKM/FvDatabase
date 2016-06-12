#include "migration.h"

void Migration::setVersion(float version)
{
    m_version = version;
}

void Migration::setDescription(QString description)
{
    m_description = description;
}

float Migration::version(void)
{
    return m_version;
}

QString Migration::description(void)
{
    return m_description;
}

int Migration::executionTime() const
{
    return m_executionTime;
}

void Migration::setExecutionTime(int executionTime)
{
    m_executionTime = executionTime;
}

QString Migration::DownSql() const
{
    return m_DownSql;
}

void Migration::setDownSql(const QString &DownSql)
{
    m_DownSql = DownSql;
}
QString Migration::UpSql() const
{
    return m_UpSql;
}

void Migration::setUpSql(const QString &UpSql)
{
    m_UpSql = UpSql;
}




