#include <QDir>
#include <QtXml>
#include <QFileDialog>
#include <iostream>

#include "databaseconfig.h"
#include "ui_databaseconfig.h"
#include "tools/tools.h"
#include "dictxml.h"
#include "inifile.h"

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

        DictXML dici;
        dici.GetFieldPropertyByName("ID","Name");
     }
}

void DatabaseConfig::retrievElements(QDomElement root, QString tag, QString att)
{
    QDomNodeList nodes = root.elementsByTagName(tag);

    qDebug() << "# nodes = " << nodes.count();
    for(int i = 0; i < nodes.count(); i++)
    {
        QDomNode elm = nodes.at(i);
        if(elm.isElement())
        {
            QDomElement e = elm.toElement();
            qDebug() << e.attribute(att);
        }
    }
}

void DatabaseConfig::on_btnCancel_clicked()
{
    QApplication::exit(1);
}
