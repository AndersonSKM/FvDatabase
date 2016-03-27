#include <QDir>
#include <QSettings>
#include <QCloseEvent>
#include <QtCore>

#include "configconnection.h"
#include "ui_configconnection.h"

#include "laycan.h"
#include "connection.h"
#include "mainwindow.h"

ConfigConnection::ConfigConnection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigConnection)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    loadSettings();

    laycan = new Laycan();
    QObject::connect(laycan, &Laycan::logChanged, this, &ConfigConnection::updateOutput);
}

ConfigConnection::~ConfigConnection()
{
    delete ui;
    delete laycan;
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
        if (data.setConection()) {
            ui->stackedWidget->setCurrentIndex(1);

            laycan->setLogFilePath(ui->edtLogFilePath->text());
            if (!laycan->Migrate(":/Migrations.xml")) {
                QMessageBox::critical(this,"",laycan->lastError());
                return;
            }

            MainWindow *m = new MainWindow();
            m->setAttribute(Qt::WA_DeleteOnClose);
            m->showMaximized();
            this->close();
        }
    }
}

void ConfigConnection::updateOutput(QString msg, LogLevel level)
{
    QColor color;
    switch(level) {
        case INFORMATION:
            color = Qt::blue;
            break;
        case WARNING:
            color = Qt::yellow;
            break;
        case ERROR:
            color = Qt::red;
            break;
    }

    ui->memoLog->append("<font color='"+color.name()+"'>"+msg+"</font>");
    ui->memoLog->update();
    QApplication::processEvents();
}

void ConfigConnection::loadSettings(void)
{
    QSettings setttings("Laycan","LaycanExemple");
    setttings.beginGroup("CONNECTION");
    ui->cbDriver->setCurrentIndex(setttings.value("DriverIndex",0).toInt());
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

    switch (ui->cbDriver->currentIndex()) {
        case 0:
            setttings.setValue("Driver", "QMYSQL");
            break;
        case 1:
            setttings.setValue("Driver", "QPSQL");
            break;
    }

    setttings.setValue("DriverIndex",ui->cbDriver->currentIndex());
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
