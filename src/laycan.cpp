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
    m_saveLogFile = false;
}

Laycan::~Laycan()
{

}

void Laycan::Migrate(const QString xmlPath)
{
    xmlFilePath = xmlPath;
    dlg = new MigrationProgress();
    dlg->setWindowFlags(Qt::CustomizeWindowHint);
    dlg->setMaximum(Migrations.count());

    putLog("[Checking the connection to the database]");
    if (!QSqlDatabase::database().isOpen()) {
        putLogError("[Error to connect to the database] : " +
                    QSqlDatabase::database().lastError().text());
    }

    InitXML();
    executeMigrations();

    delete dlg;
}

void Laycan::flushLog(QString msg)
{
    if (!logFilePath().isEmpty()) {
        QFile file(logFilePath());

        if (!file.open(QIODevice::Append | QIODevice::Text)) {
            qDebug() << "[Cannot write log file " << logFilePath() << "]";
            return;
        }

        QTextStream out(&file);
        out << "["+ QTime::currentTime().toString() +"]"  << msg << &endl;
        file.close();
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

void Laycan::setSaveLogFile(bool value)
{
    m_saveLogFile = value;
}

bool Laycan::saveLogFile(void)
{
    return m_saveLogFile;
}

QString Laycan::logFilePath(void)
{
    return m_logFilePath;
}

void Laycan::setLogFilePath(QString path)
{
    m_logFilePath = path;
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

void Laycan::putLog(QString msg)
{
    if (dlg != NULL) {
        dlg->putLog(msg,Qt::black);
        flushLog(msg);
    }
}

void Laycan::putLogError(QString msg)
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
        putLogError("[Error creating version table: " +
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
        dlg->putLog("Creating versions table");
        if (!createTableVersion())
            return;
    }

    float dbSchemaVersion = getCurrentSchemaVersion();

    loadMigrationsFromXML();

    Migration script;
    foreach (script, Migrations) {
        if (script.version() > dbSchemaVersion) {
            putLog("[Migrating version of the schema for: " + QString::number(script.version()) + "]");
            dlg->setStatus("Verifying the Migration: " + script.description());

            QSqlDatabase::database().transaction();

            bool executed = query.exec(script.SQL());
            if (executed) {
                dlg->setStatus("Running SQL: " + script.description(),"red");

                executed = writeMigrationLog(script);
            }

            if (executed) {
                QSqlDatabase::database().commit();
            } else {
                putLogError("[ERRO] Error executing SQL: " + script.description()
                          + "Error: " + query.lastError().text()
                          + " SQL: "  + query.lastQuery());
                QSqlDatabase::database().rollback();

                putLog("[Última migração executada: " + script.description() + "]");
                break;
            }
        }
        dlg->setProgress(dlg->progress()+1);
    }
    putLog("[Finalizando Migração]");
}

/* XML Functions */
void Laycan::loadMigrationsFromXML(void)
{
    putLog("[Loading File SQL scripts " + xmlFilePath + "]");
    QDomNodeList root = xml.elementsByTagName("SQL");

    if (root.isEmpty()) {
        putLogError("[No migration found in XML]");
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

    putLog("[Loaded migrations: " + QString::number(root.count()) + "]");
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

