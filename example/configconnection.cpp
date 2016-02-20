#include <QDir>
#include <QSettings>
#include <QCloseEvent>

#include "configconnection.h"
#include "ui_configconnection.h"

#include "laycan.h"
#include "mainwindow.h"
#include "connection.h"

ConfigConnection::ConfigConnection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigConnection)
{
    ui->setupUi(this);
    QSettings setttings("Laycan","LaycanExemple");

    setttings.beginGroup("CONNECTION");
    ui->edtServer->setText(setttings.value("Server").toString());
    ui->edtDatabase->setText(setttings.value("Database").toString());
    ui->edtUsuario->setText(setttings.value("User").toString());
    ui->edtSenha->setText(setttings.value("Passwd").toString());
    ui->sbPorta->setValue(setttings.value("Port").toInt());
    ui->edtLogFilePath->setText(setttings.value("LogFile").toString());
    setttings.endGroup();
}

ConfigConnection::~ConfigConnection()
{
    delete ui;
}

void ConfigConnection::on_btnOk_clicked()
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
            //d.setLogFilePath("/Users/Anderson/Desktop/laycanlog.log");

            this->hide();
            d.Migrate(":/Migrations/note.xml");

            MainWindow *m = new MainWindow;
            m->showMaximized();
        }
    }
}

void ConfigConnection::closeEvent(QCloseEvent *event)
{
    QSettings setttings("Laycan","LaycanExemple");
    setttings.beginGroup("CONNECTION");
    setttings.setValue("Server", ui->edtServer->text());
    setttings.setValue("Database", ui->edtDatabase->text());
    setttings.setValue("User", ui->edtUsuario->text());
    setttings.setValue("Passwd", ui->edtSenha->text());
    setttings.setValue("Port", ui->sbPorta->value());
    setttings.setValue("LogFile", ui->edtLogFilePath->text());
    setttings.endGroup();
}

void ConfigConnection::on_btnCancel_clicked()
{
    QApplication::exit();
}
