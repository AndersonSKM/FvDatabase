#ifndef Laycan_H
#define Laycan_H

#include <QDomDocument>

#include "migrationprogress.h"

class Migration
{
public:
    inline Migration() {}
    inline ~Migration() {}

    void setVersion(int);
    void setDescription(QString);
    void setSQL(QString);

    int version(void);
    QString description(void);
    QString SQL(void);
private:
    int m_version;
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

    //void addMigrationsExecuted(void);
    //void addVerifiedMigrations(void);
    //void addPendingMigrations(void);

    void setProgressVisible(bool visible);

    //void setVerifiedMigrations(int count);
    //void setExecutedMigrations(int count);
    //void setPendingMigrations(int count);

    bool progressVisible(void);
    //QList<Migration*> MigrationsExecuted(void);
    //QList<Migration*> PendingMigrations(void);
    //int VerifiedMigrationsCount(void);
private:
    void InitXML(QString);
    void loadMigrationsFromXML(void);
    void executeMigrations(void);

    bool writeMigrationLog(Migration&);

    QString filePath;
    QDomDocument xml;

    MigrationProgress *dlg;
    QList<Migration> Migrations;
    QList<Migration> m_ExecutedMigrations;
    QList<Migration> m_PendingMigrations;
    int m_verifiedMigrations;

    bool m_progressVisible;
};

#endif // Laycan_H
