#ifndef Laycan_H
#define Laycan_H

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
    bool createVersionTable(void);

    void setLogFilePath(QString);
    void setProgressVisible(bool);
    void setVerifiedMigrations(int);

    QString logFilePath(void);
    bool progressVisible(void);
    int verifiedMigrationsCount(void);
    int executedMigrationsCount(void);

    void setOutTextLog(QTextBrowser*);
    void setOutStatus(QLabel*);
private:
    void InitXML(QString);
    void log(QString,LogLevel = INFORMATION);
    void setStatus(QString,QColor = Qt::black);
    void loadMigrationsFromXML(void);
    void executeMigrations(void);
    void flushLog(QString msg);
    void addExecutedMigration(Migration&);

    bool writeMigrationLog(Migration&);
    float getCurrentSchemaVersion(void);

    QFile *m_logFile;
    QFile *m_xmlFile;
    QTextBrowser *m_outLog;
    QLabel *m_outStatus;

    QDomDocument m_xml;
    QList<Migration> Migrations;
    QList<Migration> m_ExecutedMigrations;
    QList<Migration> m_PendingMigrations;

    int m_verifiedMigrations;
    bool m_progressVisible;
};

#endif // Laycan_H
