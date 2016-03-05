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
    loadSettings();
}

ConfigConnection::~ConfigConnection()
{
    delete ui;
}

void ConfigConnection::on_btnOk_clicked()
{
    if (ui->edtServer->text().isEmpty()) {
        Database::Menssage("The Server field can not be empty!");
        ui->edtServer->setFocus();
    } else if (ui->edtUsuario->text().isEmpty()) {
        Database::Menssage("The User field can not be empty!");
        ui->edtUsuario->setFocus();
    } else if (ui->edtDatabase->text().isEmpty()) {
        Database::Menssage("The Database field can not be empty!");
        ui->edtDatabase->setFocus();
    } else {
        writeSettings();

        Database data;
        if ( data.setConection() ) {
            Laycan d;

            d.setOutStatus();
            d.setLogFilePath(ui->edtLogFilePath->text());

            this->hide();
            d.Migrate(":/Migrations/note.xml");

            MainWindow *m = new MainWindow;
            m->showMaximized();
        }
    }
}

void ConfigConnection::loadSettings(void)
{
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

void ConfigConnection::writeSettings(void)
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

void ConfigConnection::closeEvent()
{
    writeSettings();
}

void ConfigConnection::on_btnCancel_clicked()
{
    closeEvent();
    QApplication::exit();
}
