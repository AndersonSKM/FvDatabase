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
    logFile = nullptr;
}

Laycan::~Laycan()
{
    delete logFile;
}

void Laycan::Migrate(const QString xmlPath)
{
    xmlFilePath = xmlPath;
    dlg = new MigrationProgress();
    dlg->setWindowFlags(Qt::CustomizeWindowHint);
    dlg->setMaximum(Migrations.count());

    put("[Checking the connection to the database]");
    if (!QSqlDatabase::database().isOpen()) {
        putError("[Error to connect to the database] : " +
                    QSqlDatabase::database().lastError().text());
    } else {
        InitXML();
        executeMigrations();
    }

    delete dlg;
}

void Laycan::flushLog(QString msg)
{
    if (logFile != nullptr) {
        QTextStream out(logFile);
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
    if (logFile != nullptr)
        return logFile->fileName();

    return "";
}

void Laycan::setLogFilePath(QString path)
{
    logFile =  new QFile(path);
    if (!logFile->open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "[Cannot write log file " << logFile->fileName() << "]";
        return;
    }
}

void Laycan::addExecuteMigration(Migration &m)
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
                  " (version, description, script) "
                  "values "
                  " (:v , :d, :s)");
    query.bindValue(0, script.version());
    query.bindValue(1, script.description());
    query.bindValue(2, script.SQL());

    return query.exec();
}

float Laycan::getCurrentSchemaVersion()
{
    QSqlQuery query;
    query.exec("select max(version) from schema_version");
    query.next();
    return query.value(0).toFloat();
}

void Laycan::put(QString msg)
{
    if (dlg != NULL) {
        dlg->putLog(msg,Qt::black);
        flushLog(msg);
    }
}

void Laycan::putError(QString msg)
{
    if (dlg != NULL) {
        dlg->putLog(msg,Qt::red);
        flushLog(msg);
    }
}

bool Laycan::createTableVersion()
{
    QSqlQuery query;
    QSqlDatabase::database().transaction();

    bool executed = query.exec("CREATE TABLE schema_version ("
                           "   version FLOAT NULL, "
                           "   description VARCHAR(200) NULL,"
                           "   script TEXT NULL"
                           ");");

    if (executed) {
        QSqlDatabase::database().commit();
    } else {
        QSqlDatabase::database().rollback();
        putError("[Error creating version table: " +
                    query.lastError().text() + "]");
    }

    return executed;
}

void Laycan::executeMigrations()
{
    QSqlQuery query;

    if (progressVisible())
        dlg->show();

    if (!QSqlDatabase::database().tables().contains("schema_version")) {
        put("Creating versions table");
        if (!createTableVersion())
            return;
    }

    float dbSchemaVersion = getCurrentSchemaVersion();

    loadMigrationsFromXML();

    Migration script;
    foreach (script, Migrations) {
        if (script.version() > dbSchemaVersion) {
            put("[Migrating version of the schema for: " + QString::number(script.version()) + "]");
            dlg->setStatus("Verifying the Migration: " + script.description());

            QSqlDatabase::database().transaction();

            bool executed = query.exec(script.SQL());
            if (executed) {
                dlg->setStatus("Running SQL: " + script.description(),"red");

                executed = writeMigrationLog(script);
            }

            if (executed) {
                QSqlDatabase::database().commit();
                addExecuteMigration(script);
            } else {
                putError("[ERRO] Error executing SQL: " + script.description()
                          + "Error: " + query.lastError().text()
                          + " SQL: "  + query.lastQuery());
                QSqlDatabase::database().rollback();

                put("[Last executed SQL: " + script.description() + "]");
                break;
            }
        }
        dlg->setProgress(dlg->progress()+1);
    }
    put("[Finalizing the migration]");
    put("[Performed migrations: "+ QString::number(executedMigrationsCount()) +"]");
    put("[Pending migrations]");
}

/* XML Functions */
void Laycan::loadMigrationsFromXML(void)
{
    put("[Loading File SQL scripts " + xmlFilePath + "]");
    QDomNodeList root = xml.elementsByTagName("SQL");

    if (root.isEmpty()) {
        putError("[No migration found in XML]");
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

    put("[Loaded migrations: " + QString::number(root.count()) + "]");
}

void Laycan::InitXML()
{
    QFile file(xmlFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        QMessageBox::information(NULL,"","Erro ao abrir arquivo XML");

    if (!xml.setContent(&file)) {
        file.close();
        QMessageBox::information(NULL,"","Erro ao setar XML");
    }

    file.close();
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

