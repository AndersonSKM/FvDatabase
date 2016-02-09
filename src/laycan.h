#ifndef Laycan_H
#define Laycan_H

#include <QDomDocument>

#include "migrationprogress.h"

class Migration
{
public:
    inline Migration() {}
    inline ~Migration() {}

    void setVersion(float);
    void setDescription(QString);
    void setSQL(QString);

    float version(void);
    QString description(void);
    QString SQL(void);
private:
    float m_version;
    QString m_description;
    QString m_sql;
};

class Laycan
{
public:
    explicit Laycan();
    ~Laycan();

    void Migrate(const QString);
    bool createTableVersion(void);
    void putLog(QString);
    void putLogError(QString);

    void setLogFilePath(QString);
    void setProgressVisible(bool);
    void setVerifiedMigrations(int);
    void setSaveLogFile(bool);

    QString logFilePath(void);
    bool saveLogFile(void);
    bool progressVisible(void);
    int VerifiedMigrationsCount(void);
private:
    void InitXML(void);
    void loadMigrationsFromXML(void);
    void executeMigrations(void);
    void flushLog(QString msg);

    bool writeMigrationLog(Migration&);
    float getCurrentSchemaVersion(void);

    MigrationProgress *dlg;
    QString xmlFilePath;
    QDomDocument xml;
    QStringList log;

    QList<Migration> Migrations;
    QList<Migration> m_ExecutedMigrations;
    QList<Migration> m_PendingMigrations;

    QString m_logFilePath;
    int m_verifiedMigrations;
    bool m_progressVisible;
    bool m_saveLogFile;
};

#endif // Laycan_H
