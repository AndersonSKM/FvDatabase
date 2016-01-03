#include <QDir>
#include <QtXml>

#include "databaseconfig.h"
#include "ui_databaseconfig.h"
#include "inifile.h"
#include "connection.h"
#include "laycan.h"

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
    ui->edtDatabase->setText(ini->database());
}

DatabaseConfig::~DatabaseConfig()
{
    delete ui;
}

void DatabaseConfig::on_btnOk_clicked()
{
    if (ui->edtServer->text().isEmpty())
        Database::Menssage("Preencha o campo Servidor !");
    else if (ui->edtUsuario->text().isEmpty())
        Database::Menssage("Preencha o campo Usuário !");
    else if (ui->edtDatabase->text().isEmpty())
        Database::Menssage("Preencha o campo Banco de Dados !");
    else {
        ini->setDriverType(mysql);
        ini->setServer(ui->edtServer->text().trimmed());
        ini->setUserName(ui->edtUsuario->text().trimmed());
        ini->setPasswd(ui->edtSenha->text().trimmed());
        ini->setPort(ui->sbPorta->value());
        ini->setDatabase(ui->edtDatabase->text().trimmed());
        ini->save();

        Database data;
        if ( data.setConection(ini) ) {
            Laycan d;
            this->hide();
            d.setProgressVisible(true);
            d.Migrate(":/Migrations/note.xml");
            on_btnCancel_clicked();
        }
    }

}

void DatabaseConfig::on_btnCancel_clicked()
{
    QApplication::exit(1);
}
