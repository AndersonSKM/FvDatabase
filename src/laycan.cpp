#include <QDialog>
#include <QApplication>
#include <QtGlobal>
#include <QDomNode>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QMessageBox>

#include "laycan.h"

Laycan::Laycan()
{
    m_progressVisible = true;
}

Laycan::~Laycan()
{

}

void Laycan::Migrate(const QString xmlPath)
{
    InitXML(xmlPath);
    executeMigrations();
}

void Laycan::setProgressVisible(bool visible)
{
    m_progressVisible = visible;
}

bool Laycan::progressVisible()
{
    return m_progressVisible;
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
        qDebug() << "[Erro Ao Criar Tabela de Versão: "
                 << query.lastError().text() << "]";
    }

    return executed;
}

void Laycan::executeMigrations()
{
    QSqlQuery query;

    dlg = new MigrationProgress();
    dlg->setWindowFlags( Qt::CustomizeWindowHint );
    dlg->setMaximum(Migrations.count());

    if (progressVisible())
        dlg->show();

    if (!QSqlDatabase::database().tables().contains("schema_version")) {
        dlg->putLog("Criando Tabela de Versão");
        if (!createTableVersion())
            return;
    }

    float dbSchemaVersion = getCurrentSchemaVersion();

    loadMigrationsFromXML();

    Migration script;
    foreach (script, Migrations) {
        if (script.version() > dbSchemaVersion) {
            qDebug() << "[Migrando a versão do schema para: " << script.version() << "]";
            dlg->setStatus("Verificando Migração: " + script.description());

            QSqlDatabase::database().transaction();

            bool executed = query.exec(script.SQL());
            if (executed) {
                dlg->setStatus("Executando sql: " + script.description(),"red");

                executed = writeMigrationLog(script);
            }

            if (executed) {
                QSqlDatabase::database().commit();
            } else {
                qDebug() << "[ERRO] Erro ao executar sql: " << script.description() << endl
                         << "Erro: " << query.lastError().text() << endl
                         << " SQL: " << query.lastQuery();
                QSqlDatabase::database().rollback();

                qDebug() << "[Última migração executada: " << script.description() << "]";
                break;
            }
        }
        dlg->setProgress(dlg->progress()+1);
    }
    qDebug() << "[Finalizando Migração]";

    delete dlg;
}

/* XML Functions */
void Laycan::loadMigrationsFromXML(void)
{
    qDebug() << "[Carregando scripts do arquivo " << filePath << "]";
    QDomNodeList root = xml.elementsByTagName("SQL");

    if (root.isEmpty()) {
        qDebug() << "[Nenhuma migração encontrada no XML]";
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

    qDebug() << "[Migrações carregadas: " << root.count() << "]";
}

void Laycan::InitXML(QString xmlPath)
{
    filePath = xmlPath;
    QFile file(filePath);
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

