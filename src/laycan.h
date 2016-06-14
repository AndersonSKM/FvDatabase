#ifndef Laycan_H
#define Laycan_H

#include <QObject>
#include <QTime>
#include <QVariant>
#include <QApplication>
#include <QDebug>
#include <QTextStream>
#include <QLabel>
#include <QDialog>
#include <QtGlobal>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QMessageBox>
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QSqlDriver>

#include "schemaversion.h"
#include "logger.h"
#include "migration.h"

class Laycan : public QObject
{
    Q_OBJECT
public:
    explicit Laycan(QObject* parent = nullptr);
    virtual ~Laycan();

    bool Migrate(const QString &jsonFilePath);

    QString logFilePath(void);
    void setLogFilePath(const QString &filePath);

    int verifiedMigrationsCount(void) const;
    void setVerifiedMigrations(const int value);

    int executedMigrationsCount(void) const;

    LaycanLogger* Logger();
    void setLogger(LaycanLogger &logger);

    QString lastError() const;
    void setLastError(const QString &lastError);

    QString tableVersionName() const;
    void setTableVersionName(const QString &name);

    float currentVersion();

    bool autoCommit() const;
    void setAutoCommit(bool autoCommit);

signals:
    void logChanged(QString,LogLevel);

private:
    bool executeMigrations(void);
    bool parseJson(const QJsonObject &json);
    void addExecutedMigration(Migration &);
    void rollbackMigration(const Migration &m);

    void log(LogLevel level, const QString &msg);
    void logList(const QStringList &list);
    void log(const QString &msg);

    bool m_autoCommit;
    QString m_lastError;

    LaycanLogger *m_logger;
    SchemaVersion m_dbVersion;

    QList<Migration> m_migrations;
    QList<Migration> m_ExecutedMigrations;
    QList<Migration> m_PendingMigrations;

    int m_verifiedMigrations;
};

#endif // Laycan_H
