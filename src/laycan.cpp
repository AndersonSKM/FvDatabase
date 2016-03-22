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

void Laycan::Migrate(const QString &xmlPath)
{
    log("Checking the connection to the database");
    if (!QSqlDatabase::database().isOpen()) {
        log(ERROR,"Error to connect to the database : " +
            QSqlDatabase::database().lastError().text());
    } else {

        QFile xmlFile(xmlPath);
        if (!xmlFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            log(ERROR,"Error opening XML file");
            return;
        }

        if (!getXml().setContent(&xmlFile)) {
            log(ERROR,"Error when selecting XML file");
            xmlFile.close();
            return;
        }

        xmlFile.close();
        executeMigrations();
    }
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

bool Laycan::writeMigrationLog(Migration &script)
{
    QSqlQuery query;
    query.prepare("insert into schema_version"
                  " (version, description, script, datehour) "
                  "values "
                  " (:v , :d, :s, :h)");
    query.bindValue(0, script.version());
    query.bindValue(1, script.description());
    query.bindValue(2, script.SQL());
    query.bindValue(3, QDateTime::currentDateTime()
                        .toString("dd-MM-yyyy - hh:mm:ss"));

    return query.exec();
}

float Laycan::getCurrentSchemaVersion()
{
    QSqlQuery query;
    query.exec("select max(version) from schema_version");
    query.next();
    return query.value(0).toFloat();
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
}

void Laycan::log(const QString &msg)
{
    log(INFORMATION,msg);
}

bool Laycan::createVersionTable()
{
    QSqlQuery query;
    QSqlDatabase::database().transaction();

    bool executed;
    executed = query.exec("CREATE TABLE schema_version ("
                          "   version FLOAT NULL, "
                          "   description VARCHAR(200) NULL,"
                          "   script TEXT NULL,"
                          "   datehour VARCHAR(15) NULL"
                          ");");

    if (executed) {
        QSqlDatabase::database().commit();
    } else {
        QSqlDatabase::database().rollback();
        log(ERROR,"Error creating version table: " +
                    query.lastError().text() + "]");
    }

    return executed;
}

void Laycan::executeMigrations()
{
    log("Checking versions table");
    if (!m_schemaversion.checkVersionTable()) {
        log("Error creating version table :" + m_schemaversion.lastError());
        return;
    }

    float dbSchemaVersion = m_schemaversion.version();

    loadMigrationsFromXML();

    Migration script;
    foreach (script, Migrations) {

        if (script.version() > dbSchemaVersion) {
            log("Migrating version of the schema for: " + QString::number(script.version()));

            QSqlDatabase::database().transaction();
            QSqlQuery query;

            bool executed = query.exec(script.SQL());
            if (executed) {
                executed = m_schemaversion.writeDbChanges(script);
            }

            if (executed) {
                QSqlDatabase::database().commit();
                addExecutedMigration(script);
            } else {
                QSqlDatabase::database().rollback();
                log(ERROR,"Error executing SQL: " + script.description()
                          + " Error: " + query.lastError().text()
                          + " SQL: "  + query.lastQuery());

                break;
            }
        }
        QApplication::processEvents();
    }
    log("Finalizing the migration");
    log("Performed migrations: "+ QString::number(executedMigrationsCount()));
    log("Pending migrations");
}

/* XML Functions */

void Laycan::loadMigrationsFromXML(void)
{
    log("Loading File SQL scripts ");
    QDomNodeList root = getXml().elementsByTagName("SQL");

    if (root.isEmpty()) {
        log(ERROR,"No migration found in XML");
        return;
    }

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

        Migrations.append(script);
    }

    log("Loaded migrations: " + QString::number(root.count()));
}

/* End XML Functions */
