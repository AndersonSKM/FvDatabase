#include "dlgopenfile.h"
#include "ui_dlgopenfile.h"
#include "laycaneditor.h"

#include <QSettings>
#include <QFileDialog>
#include <QMessageBox>
#include <QDomDocument>

DlgOpenFile::DlgOpenFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgOpenFile)
{
    ui->setupUi(this);

    settings = new QSettings("Laycan","LaycanEditor");
    ui->edtFile->setText(settings->value("MigrationFile").toString());
}

DlgOpenFile::~DlgOpenFile()
{
    delete ui;
    delete settings;
}

void DlgOpenFile::closeEvent()
{
    settings->setValue("MigrationFile", ui->edtFile->text());
}

void DlgOpenFile::on_btnCancel_clicked()
{
    closeEvent();
    QApplication::exit();
}

void DlgOpenFile::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Migration File"), QDir::homePath(), tr("Laycan file (*.xml)"));
    ui->edtFile->setText(fileName);
}

void DlgOpenFile::on_btnOpen_clicked()
{
    if (ui->edtFile->text().isEmpty()) {
        QMessageBox::information(this,"","File can't be empty !");
        return;
    }

    QFile xmlFile(ui->edtFile->text());
    if (!xmlFile.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QMessageBox::critical(this,"","Error opening XML file");
        return;
    }

    QDomDocument xml;
    if (!xml.setContent(&xmlFile)) {
        QMessageBox::critical(this,"","Invalid XML file");
        xmlFile.close();
        return;
    }

    LaycanEditor *laycanEditor = new LaycanEditor;
    laycanEditor->setAttribute(Qt::WA_DeleteOnClose);
    laycanEditor->setFixedSize(laycanEditor->width(), laycanEditor->height());
    laycanEditor->setXml(xml);
    laycanEditor->show();
    this->close();
}
