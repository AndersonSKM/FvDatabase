#include "laycan.h"
#include "logger.h"

Laycan::Laycan(QObject* parent) : QObject(parent)
{
    m_autoCommit = false;
    m_logger = new LaycanLogger;
}

Laycan::~Laycan()
{
    delete m_logger;
}

bool Laycan::Migrate(const QString &jsonFilePath)
{
    log("Checking the connection to the database");

    if (!QSqlDatabase::database().isOpen()) {
        log(ERROR,QString("Error to connect to the database : %1")
                    .arg(QSqlDatabase::database().lastError().text()));
        return false;
    }

    log("Validating json file");

    QFile file(jsonFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        log(ERROR,"Error opening Json file");
        return false;
    }

    QByteArray jsonData = file.readAll();
    file.close();
    if (file.error() != QFile::NoError) {
        log(ERROR,file.errorString());
        return false;
    }

    if (jsonData.isEmpty()) {
        log(ERROR,"No data was currently available for reading from file");
        return false;
    }

    QJsonParseError parseError;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(jsonData,&parseError));
    if (parseError.error != QJsonParseError::NoError) {
        log(ERROR,parseError.errorString());
        return false;
    }

    if (!jsonDoc.isObject()) {
        log(ERROR,"Document is not an object");
        return false;
    }

    if (! parseJson(jsonDoc.object()) ) {
        log(ERROR, "Filed to parse json file");
        return false;
    }

    return executeMigrations();
}

QString Laycan::logFilePath()
{
    return Logger()->fileName();
}

void Laycan::setLogFilePath(const QString &filePath)
{
    if (filePath.isEmpty())
        return;

    Logger()->setFile(filePath);
}

void Laycan::addExecutedMigration(Migration &m)
{
    m_ExecutedMigrations.append(m);
}

void Laycan::rollbackMigration(const Migration &m)
{
    log("Executing rollback sql");
    QSqlQuery query;
    if (!query.exec(m.DownSql())) {
        log(ERROR,query.lastError().text());
    }
}

int Laycan::executedMigrationsCount() const
{
    return m_ExecutedMigrations.count();
}

LaycanLogger *Laycan::Logger()
{
    return m_logger;
}

void Laycan::setLogger(LaycanLogger &logger)
{
    m_logger = &logger;
}

void Laycan::log(LogLevel level, const QString &msg)
{
    Logger()->write(level,msg);
    emit logChanged(msg,level);

    if (level == ERROR) setLastError(msg);
}

void Laycan::logList(const QStringList &list)
{
    foreach (const QString &s, list) {
        log(s);
    }
}

void Laycan::log(const QString &msg)
{
    log(INFORMATION,msg);
}

bool Laycan::autoCommit() const
{
    return m_autoCommit;
}

void Laycan::setAutoCommit(bool autoCommit)
{
    m_autoCommit = autoCommit;
}

QString Laycan::lastError() const
{
    return m_lastError;
}

void Laycan::setLastError(const QString &lastError)
{
    m_lastError = lastError;
}

QString Laycan::tableVersionName() const
{
    return m_dbVersion.tableName();
}

void Laycan::setTableVersionName(const QString &name)
{
    m_dbVersion.setTableName(name);
}

float Laycan::currentVersion()
{
    m_dbVersion.loadCurrentVersion();
    return m_dbVersion.version();
}

bool Laycan::executeMigrations()
{
    log("Checking versions table");
    if (!m_dbVersion.checkVersionTable()) {
        log(ERROR,m_dbVersion.lastError());
        return false;
    }

    bool inTransaction;
    bool hasTransactions = (QSqlDatabase::database().driver()->
                                hasFeature(QSqlDriver::Transactions) && (m_autoCommit = false));

    foreach (Migration script, m_migrations) {
        m_dbVersion.loadVersion(script.version());

        if (!m_dbVersion.isExecuted()) {

            log(QString("Migrating version of the schema for: %1")
                    .arg(script.version()));

            if (hasTransactions) {
                inTransaction = QSqlDatabase::database().transaction();
            } else {
                inTransaction = false;
            }

            QSqlQuery query;
            QTime timer;

            log(QString("Executing migration: %1").arg(script.description()));
            timer.start();

            if (!query.exec(script.UpSql())) {
                log(ERROR,QString("Error executing SQL: %1 Error: %2 SQL: %3")
                            .arg(script.description())
                            .arg(query.lastError().text())
                            .arg(query.lastQuery()));

                if (inTransaction) {
                    QSqlDatabase::database().rollback();
                } else {
                    rollbackMigration(script);
                }

                return false;
            }

            script.setExecutionTime(timer.elapsed());

            log(QString("Saving database changes, execution time: %1")
                  .arg(script.executionTime()));

            if (!m_dbVersion.writeDbChanges(script)) {
                log(ERROR,m_dbVersion.lastError());

                if (inTransaction) {
                    QSqlDatabase::database().rollback();
                } else {
                    rollbackMigration(script);
                }

                return false;
            }

            if (inTransaction) {
                QSqlDatabase::database().commit();
            }

            addExecutedMigration(script);
        }
        QApplication::processEvents();
    }
    log("Finalizing the migration");

    log(QString("Performed migrations: %1")
          .arg(executedMigrationsCount()));

    log("Pending migrations");
    return true;
}

bool Laycan::parseJson(const QJsonObject &json)
{
    log("Parse json to Migration Object");

    QJsonArray migrations = json["Migrations"].toArray();

    //Read all migrations
    foreach (const QJsonValue &v, migrations) {
        QJsonObject migration = v.toObject();
        Migration script;

        //Add all propertys of migration
        script.setVersion(migration["Version"].toString().toFloat());
        script.setDescription(migration["Description"].toString());

        QStringList sql;

        //UpVersion SQL
        QJsonArray upVersionArray = migration["UpVersion"].toArray();
        foreach (const QJsonValue &u, upVersionArray) {
            sql.append(u.toString());
        }

        script.setUpSql(sql.join("\n"));
        sql.clear();

        //DownVersion SQL
        QJsonArray downVersionArray = migration["DownVersion"].toArray();
        foreach (const QJsonValue &d, downVersionArray) {
            sql.append(d.toString());
        }

        script.setDownSql(sql.join('\n'));

        //Append migration on list
        m_migrations.append(script);
    }

    log("Loaded migrations: " + QString::number(migrations.count()));
    return true;
}
