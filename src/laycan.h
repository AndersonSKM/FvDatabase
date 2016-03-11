#ifndef Laycan_H
#define Laycan_H

#include <QObject>
#include <QTime>
#include <QDomDocument>
#include <QVariant>
#include <QFile>
#include <QApplication>
#include <QDebug>
#include <QTextStream>
#include <QTextBrowser>
#include <QLabel>
#include <QPointer>
#include <QDialog>
#include <QtGlobal>
#include <QDomNode>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QMessageBox>
#include <QDateTime>

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

enum LogLevel {
    ERROR,
    WARNING,
    INFORMATION,
};

enum StatusLevel {
    RUNING,
    CHECKING,
    SAVING,
};

class Laycan : public QObject
{
    Q_OBJECT
public:
    explicit Laycan(QObject* parent = nullptr );
    virtual ~Laycan();

    void Migrate(const QString);
    bool createVersionTable(void);

    void setLogFilePath(QString);
    void setProgressVisible(bool);
    void setVerifiedMigrations(int);
    void setStatus(QString, StatusLevel = RUNING);

    QString logFilePath(void);
    bool progressVisible(void);
    int verifiedMigrationsCount(void);
    int executedMigrationsCount(void);
    QString status(void);

    void log(QString,LogLevel = INFORMATION);
signals:
    void logChanged(QString,LogLevel);
    void statusChanged(QString,StatusLevel);

private:
    void InitXML(QString);
    void loadMigrationsFromXML(void);
    void executeMigrations(void);
    void flushLog(QString msg);
    void addExecutedMigration(Migration&);

    bool writeMigrationLog(Migration&);
    float getCurrentSchemaVersion(void);

    QFile *m_logFile;
    QFile *m_xmlFile;

    QString m_status;
    QStringList m_outLog;

    QDomDocument m_xml;
    QList<Migration> Migrations;
    QList<Migration> m_ExecutedMigrations;
    QList<Migration> m_PendingMigrations;

    int m_verifiedMigrations;
    bool m_progressVisible;
};

#endif // Laycan_H
