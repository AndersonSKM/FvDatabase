
#include "laycan.h"

Laycan::Laycan(QObject* parent) : QObject(parent)
{
    m_progressVisible = true;
    m_logFile = nullptr;
    m_xmlFile = nullptr;
}

Laycan::~Laycan()
{
    delete m_logFile;
    delete m_xmlFile;
}

void Laycan::Migrate(const QString xmlPath)
{
    log("Checking the connection to the database");
    if (!QSqlDatabase::database().isOpen()) {
        log("Error to connect to the database : " +
            QSqlDatabase::database().lastError().text(),ERROR);
    } else {
        InitXML(xmlPath);
        executeMigrations();
    }
}

void Laycan::flushLog(QString msg)
{
    if (m_logFile) {
        QTextStream out(m_logFile);
        QDateTime dateTime = QDateTime::currentDateTime();
        QString logMessage = QString("[%1] : %3")
                                .arg(dateTime.toString("dd/MM/yyyy - hh:mm:ss"))
                                .arg(msg);
        out << logMessage << &endl;
    }
}

void Laycan::setProgressVisible(bool visible)
{
    m_progressVisible = visible;
}

bool Laycan::progressVisible()
{
    return m_progressVisible;
}

QString Laycan::logFilePath()
{
    if (m_logFile != nullptr)
        return m_logFile->fileName();

    return "";
}

void Laycan::setLogFilePath(QString path)
{
    if (path.isEmpty())
        return;

    m_logFile = new QFile(path);
    if (!m_logFile->open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "[Cannot write log file " << m_logFile->fileName() << "]";
        m_logFile = nullptr;
        return;
    }
}

void Laycan::addExecutedMigration(Migration &m)
{
    m_ExecutedMigrations.append(m);
}

int Laycan::executedMigrationsCount()
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

    setStatus("Saving Updates",SAVING);
    return query.exec();
}

float Laycan::getCurrentSchemaVersion()
{
    QSqlQuery query;
    query.exec("select max(version) from schema_version");
    query.next();
    return query.value(0).toFloat();
}

void Laycan::log(QString msg, LogLevel level)
{
    switch(level) {
        case INFORMATION:
            msg = "[" + msg + "]";
            break;
        case WARNING:
            msg = "[WARNING] :" + msg;
            break;
        case ERROR:
            msg = "[ERROR]: " + msg;
            break;
    }

    emit logChanged(msg,level);
    flushLog(msg);
}

void Laycan::setStatus(QString value,StatusLevel status)
{
    if (m_status != value) {
        m_status = value;
        emit statusChanged(value,status);
    }
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
        log("Error creating version table: " +
                    query.lastError().text() + "]",ERROR);
    }

    return executed;
}

void Laycan::executeMigrations()
{
    QSqlQuery query;

    if (!QSqlDatabase::database().tables().contains("schema_version")) {
        log("Creating versions table");
        if (!createVersionTable())
            return;
    }

    float dbSchemaVersion = getCurrentSchemaVersion();

    loadMigrationsFromXML();

    Migration script;
    foreach (script, Migrations) {

        setStatus("Verifying versions",CHECKING);

        if (script.version() > dbSchemaVersion) {
            log("Migrating version of the schema for: " + QString::number(script.version()));

            QSqlDatabase::database().transaction();

            bool executed = query.exec(script.SQL());
            if (executed) {
                setStatus("Runing Migration: " + script.description(),RUNING);
                executed = writeMigrationLog(script);
            }

            if (executed) {
                QSqlDatabase::database().commit();
                addExecutedMigration(script);
            } else {
                log("Error executing SQL: " + script.description()
                          + " Error: " + query.lastError().text()
                          + " SQL: "  + query.lastQuery(),ERROR);
                QSqlDatabase::database().rollback();

                log("Last executed SQL: " + script.description());
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
    log("Loading File SQL scripts " + m_xmlFile->fileName() + "");
    QDomNodeList root = m_xml.elementsByTagName("SQL");

    if (root.isEmpty()) {
        log("No migration found in XML",ERROR);
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

void Laycan::InitXML(QString path)
{
    m_xmlFile = new QFile(path);
    if (!m_xmlFile->open(QIODevice::ReadOnly | QIODevice::Text))
        log("Error opening XML file",ERROR);

    if (!m_xml.setContent(m_xmlFile)) {
        m_xmlFile->close();
        log("Error when selecting XML file",ERROR);
    }

    m_xmlFile->close();
}

/* End XML Functions */

void Migration::setVersion(float version)
{
    m_version = version;
}

void Migration::setDescription(QString description)
{
    m_description = description;
}

void Migration::setSQL(QString sql)
{
    m_sql = sql;
}

float Migration::version(void)
{
    return m_version;
}

QString Migration::description(void)
{
    return m_description;
}

QString Migration::SQL(void)
{
    return m_sql;
}

