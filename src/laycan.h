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
    DEBUG
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
    void InitXML(void);
    void loadMigrationsFromXML(void);
    void executeMigrations(void);
    void flushLog(QString msg);
    void addExecuteMigration(Migration&);

    bool writeMigrationLog(Migration&);
    float getCurrentSchemaVersion(void);

    MigrationProgress *dlg;
    QString xmlFilePath;
    QDomDocument xml;

    QFile *logFile;

    QList<Migration> Migrations;
    QList<Migration> m_ExecutedMigrations;
    QList<Migration> m_PendingMigrations;

    QString m_logFilePath;
    int m_verifiedMigrations;
    bool m_progressVisible;
};

#endif // Laycan_H
