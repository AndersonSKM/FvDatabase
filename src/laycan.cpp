#include <QDialog>
#include <QApplication>
#include <QtGlobal>
#include <QDomNode>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QMessageBox>
#include <QDateTime>

#include "laycan.h"

Laycan::Laycan()
{
    m_progressVisible = true;
    m_logFile = nullptr;
    m_xmlFile = nullptr;
    dlg = nullptr;
}

Laycan::~Laycan()
{
    delete m_logFile;
}

void Laycan::Migrate(const QString xmlPath)
{
    dlg = new MigrationProgress();
    dlg->setWindowFlags(Qt::CustomizeWindowHint);

    log("Checking the connection to the database");
    if (!QSqlDatabase::database().isOpen()) {
        log("Error to connect to the database : " +
            QSqlDatabase::database().lastError().text(),ERROR);
    } else {
        InitXML(xmlPath);
        executeMigrations();
    }

    delete dlg;
}

void Laycan::flushLog(QString msg)
{
    if (m_logFile != nullptr) {
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
    QColor colorMsg;
    switch(level) {
        case INFORMATION:
            colorMsg = Qt::black;
            msg = "[" + msg + "]";
            break;
        case WARNING:
            colorMsg = Qt::yellow;
            msg = "[WARNING] :" + msg;
            break;
        case ERROR:
            colorMsg = Qt::red;
            msg = "[ERROR]: " + msg;
            break;
    }

    if (dlg != nullptr) {
        dlg->putLog(msg,colorMsg);
    }
    flushLog(msg);
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

    if (progressVisible())
        dlg->show();

    if (!QSqlDatabase::database().tables().contains("schema_version")) {
        log("Creating versions table");
        if (!createVersionTable())
            return;
    }

    float dbSchemaVersion = getCurrentSchemaVersion();

    loadMigrationsFromXML();

    dlg->setMaximum(Migrations.count());

    Migration script;
    foreach (script, Migrations) {
        dlg->setStatus("Verifying the Migration: " + script.description());
        if (script.version() > dbSchemaVersion) {
            log("Migrating version of the schema for: " + QString::number(script.version()));

            QSqlDatabase::database().transaction();

            dlg->setStatus("Running SQL: " + script.description(),Qt::red);
            bool executed = query.exec(script.SQL());
            if (executed) {
                dlg->setStatus("Saving changes to the database",Qt::green);
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
        dlg->setProgress(dlg->progress()+1);
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

