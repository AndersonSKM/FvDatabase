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

#include "schemaversion.h"
#include "logger.h"
#include "migration.h"


class Laycan : public QObject
{
    Q_OBJECT
public:
    explicit Laycan(QObject* parent = nullptr);
    virtual ~Laycan();

    void Migrate(const QString &xmlPath);
    bool createVersionTable(void);

    QString logFilePath(void);
    void setLogFilePath(const QString &filePath);

    int verifiedMigrationsCount(void) const;
    void setVerifiedMigrations(const int value);

    int executedMigrationsCount(void) const;

    LaycanLogger* Logger();
    void setLogger(LaycanLogger &logger);

    QDomDocument& getXml();
    void setXml(QDomDocument &xml);

signals:
    void logChanged(QString,LogLevel);

private:
    void loadMigrationsFromXML(void);
    void executeMigrations(void);
    void flushLog(QString msg);
    void addExecutedMigration(Migration&);
    void log(LogLevel level, const QString &msg);
    void log(const QString &msg);

    bool writeMigrationLog(Migration&);
    float getCurrentSchemaVersion(void);

    LaycanLogger *m_logger;
    QDomDocument m_xml;
    SchemaVersion m_schemaversion;

    QList<Migration> Migrations;
    QList<Migration> m_ExecutedMigrations;
    QList<Migration> m_PendingMigrations;

    int m_verifiedMigrations;
};

#endif // Laycan_H
