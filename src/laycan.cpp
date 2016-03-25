#include "laycan.h"
#include "logger.h"

Laycan::Laycan(QObject* parent) : QObject(parent)
{
    m_logger = new LaycanLogger;
}

Laycan::~Laycan()
{
    delete m_logger;
}

bool Laycan::Migrate(const QString &xmlPath)
{
    log("Checking the connection to the database");
    if (!QSqlDatabase::database().isOpen()) {
        log(ERROR,QString("Error to connect to the database : %1")
                    .arg(QSqlDatabase::database().lastError().text()));
        return false;
    }

    QFile xmlFile(xmlPath);
    if (!xmlFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        log(ERROR,"Error opening XML file");
        return false;
    }

    if (!getXml().setContent(&xmlFile)) {
        log(ERROR,"Error when selecting XML file");
        xmlFile.close();
        return false;
    }

    if (!assingXml()) {
        log(ERROR,"No migration found in XML");
        xmlFile.close();
        return false;
    }

    xmlFile.close();
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

int Laycan::executedMigrationsCount() const
{
    return m_ExecutedMigrations.count();
}

QDomDocument& Laycan::getXml()
{
    return m_xml;
}

void Laycan::setXml(QDomDocument &xml)
{
    m_xml = xml;
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
    for (auto it = list.begin(); it != list.end(); ++it) {
        QString current = *it;
        log(current);
    }
}

void Laycan::log(const QString &msg)
{
    log(INFORMATION,msg);
}

QString Laycan::LastError() const
{
    return m_lastError;
}

void Laycan::setLastError(const QString &lastError)
{
    m_lastError = lastError;
}


bool Laycan::executeMigrations()
{
    log("Checking versions table");
    if (!m_schemaversion.checkVersionTable()) {
        log(m_schemaversion.lastError());
        return false;
    }

    float dbSchemaVersion = m_schemaversion.version();

    foreach (Migration script, m_migrations) {

        if (script.version() > dbSchemaVersion) {
            log(QString("Migrating version of the schema for: %1")
                    .arg(script.version()));

            QSqlDatabase::database().transaction();
            QSqlQuery query;
            QTime timer;

            log(QString("Executing migration: %1").arg(script.description()));
            timer.start();

            if (!query.exec(script.SQL())) {
                QSqlDatabase::database().rollback();
                log(ERROR,QString("Error executing SQL: %1 Error: %2 SQL: %3")
                            .arg(script.description())
                            .arg(query.lastError().text())
                            .arg(query.lastQuery()));
                return false;
            }

            script.setExecutionTime(timer.elapsed());
            log(QString("Saving database changes, execution time: %1").arg(script.executionTime()));

            if (!m_schemaversion.writeDbChanges(script)) {
                QSqlDatabase::database().rollback();
                log(ERROR,m_schemaversion.lastError());
                return false;
            }

            QSqlDatabase::database().commit();
            addExecutedMigration(script);
        }
        QApplication::processEvents();
    }
    log("Finalizing the migration");
    log(QString("Performed migrations: %1").arg(executedMigrationsCount()));
    log("Pending migrations");
    return true;
}

bool Laycan::assingXml()
{
    log("Loading File SQL scripts ");
    QDomNodeList root = getXml().elementsByTagName("SQL");

    if (root.isEmpty())
        return false;

    for (int i = 0; i != root.count(); i++) {
        QDomNode migrationNode = root.at(i);
        Migration script;

        if (migrationNode.isElement()) {
            QDomElement migration = migrationNode.toElement();
            QString version = migration.attribute("version");

            script.setVersion(version.toFloat());
            script.setDescription(migration.attribute("id", "Update schema to version " + version));
        }

        // SQL in comment node
        QDomNode sql = migrationNode.firstChild();
        if (sql.nodeType() == 8) {
            script.setSQL(sql.nodeValue());
        }

        m_migrations.append(script);
    }

    log("Loaded migrations: " + QString::number(root.count()));
    return true;
}
