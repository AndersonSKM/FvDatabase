#include <QDir>
#include <QtXml>
#include <QFileDialog>
#include <iostream>

#include "databaseconfig.h"
#include "ui_databaseconfig.h"
#include "tools/tools.h"
#include "dictxml.h"
#include "inifile.h"
#include "connection.h"

DatabaseConfig::DatabaseConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DatabaseConfig)
{
    ui->setupUi(this);

    ini = new IniFile(QCoreApplication::applicationDirPath() + QDir::separator() +"Conn.ini");
    ui->edtServer->setText(ini->server());
    ui->edtUsuario->setText(ini->userName());
    ui->edtSenha->setText(ini->passwd());
    ui->sbPorta->setValue(ini->port());
}

DatabaseConfig::~DatabaseConfig()
{
    delete ui;
}

void DatabaseConfig::on_btnOk_clicked()
{
    if (ui->edtServer->text().isEmpty())
        Menssage("Preencha o campo Servidor !");
    else if (ui->edtUsuario->text().isEmpty())
        Menssage("Preencha o campo Usuário !");
    else
    {
        ini->setDriverType(mysql);
        ini->setServer(ui->edtServer->text().trimmed());
        ini->setUserName(ui->edtUsuario->text().trimmed());
        ini->setPasswd(ui->edtSenha->text().trimmed());
        ini->setPort(ui->sbPorta->value());
        ini->save();

        if ( Database::instance()->setConection(ini) )
        {
            Dictionary d(Database::instance()->m_db);
            d.Migrate(":/Migrations/note.xml");
        }
     }
}

void DatabaseConfig::on_btnCancel_clicked()
{
    QApplication::exit(1);
}
