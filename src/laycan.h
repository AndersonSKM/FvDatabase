#ifndef Laycan_H
#define Laycan_H

#include <QObject>
#include <QTime>
#include <QDomDocument>
#include <QVariant>
#include <QApplication>
#include <QDebug>
#include <QTextStream>
#include <QLabel>
#include <QDialog>
#include <QtGlobal>
#include <QDomNode>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QMessageBox>
#include <QDateTime>
#include <QException>

#include "schemaversion.h"
#include "logger.h"
#include "migration.h"

class Laycan : public QObject
{
    Q_OBJECT
public:
    explicit Laycan(QObject* parent = nullptr);
    virtual ~Laycan();

    bool Migrate(const QString &xmlPath);

    QString logFilePath(void);
    void setLogFilePath(const QString &filePath);

    int verifiedMigrationsCount(void) const;
    void setVerifiedMigrations(const int value);

    int executedMigrationsCount(void) const;

    LaycanLogger* Logger();
    void setLogger(LaycanLogger &logger);

    QDomDocument& getXml();
    void setXml(QDomDocument &xml);

    QString lastError() const;
    void setLastError(const QString &lastError);

    QString tableVersionName() const;
    void setTableVersionName(const QString &name);

    float schemaVersion();

signals:
    void logChanged(QString,LogLevel);

private:
    bool assingXml(void);
    bool executeMigrations(void);
    void addExecutedMigration(Migration&);

    void log(LogLevel level, const QString &msg);
    void logList(const QStringList &list);
    void log(const QString &msg);

    QString m_lastError;

    LaycanLogger *m_logger;
    QDomDocument m_xml;
    SchemaVersion m_schemaversion;

    QList<Migration> m_migrations;
    QList<Migration> m_ExecutedMigrations;
    QList<Migration> m_PendingMigrations;

    int m_verifiedMigrations;
};

#endif // Laycan_H
