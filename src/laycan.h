#ifndef Laycan_H
#define Laycan_H

#include <QTime>
#include <QDomDocument>
#include <QVariant>
#include <QFile>
#include <QApplication>
#include <QDebug>
#include <QTextStream>


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

enum LogLevel
{
    ERROR,
    WARNING,
    INFORMATION,
};

class Laycan
{
public:
    explicit Laycan();
    ~Laycan();

    void Migrate(const QString);
    bool createTableVersion(void);
    void log(QString,LogLevel = INFORMATION);

    void setLogFilePath(QString);
    void setProgressVisible(bool);
    void setVerifiedMigrations(int);

    QString logFilePath(void);
    bool progressVisible(void);
    int verifiedMigrationsCount(void);
    int executedMigrationsCount(void);
private:
    void InitXML(QString);
    void loadMigrationsFromXML(void);
    void executeMigrations(void);
    void flushLog(QString msg);
    void addExecutedMigration(Migration&);

    bool writeMigrationLog(Migration&);
    float getCurrentSchemaVersion(void);

    MigrationProgress *dlg;

    QFile *m_logFile;
    QFile *m_xmlFile;

    QDomDocument m_xml;
    QList<Migration> Migrations;
    QList<Migration> m_ExecutedMigrations;
    QList<Migration> m_PendingMigrations;

    int m_verifiedMigrations;
    bool m_progressVisible;
};

#endif // Laycan_H
