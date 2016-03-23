#ifndef SCHEMAVERSION_H
#define SCHEMAVERSION_H

#include <QString>
#include <QDateTime>
#include <QSqlDatabase>

#include "migration.h"

class Migration;

class SchemaVersion
{
public:
    SchemaVersion();
    ~SchemaVersion();

    bool checkVersionTable();
    bool writeDbChanges(Migration &migration);

    QString tableName() const;
    void setTableName(const QString &tableName);

    float version() const;
    void setVersion(float version);

    QString description() const;
    void setDescription(const QString &description);

    int executionTime() const;
    void setExecutionTime(int executionTime);

    QDateTime executedOn() const;
    void setExecutedOn(const QDateTime &executedOn);

    QString script() const;
    void setScript(const QString &script);

    QString lastError() const;
    void setLastError(const QString &lastError);

    QString lastSqlInsert() const;
    void setLastSqlInsert(const QString &lastSqlInsert);

private:
    bool createVersionTable();
    void loadCurrentVersion();

    QString m_lastError;
    QString m_lastSqlInsert;

    QString m_tableName;
    float m_version;
    QString m_description;
    QString m_script;
    QDateTime m_executedOn;
    int m_executionTime;
};

#endif // SCHEMAVERSION_H
