#include "dlgopenfile.h"
#include "ui_dlgopenfile.h"

#include <QSettings>
#include <QFileDialog>
#include <QMessageBox>
#include <QDomDocument>

DlgOpenFile::DlgOpenFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgOpenFile)
{
    ui->setupUi(this);
    this->setResult(QDialog::Rejected);

    settings = new QSettings("Laycan","LaycanEditor");
    ui->edtFile->setText(settings->value("MigrationFile").toString());
}

DlgOpenFile::~DlgOpenFile()
{
    delete ui;
    delete settings;
}

void DlgOpenFile::on_btnCancel_clicked()
{
    this->reject();
}

QString DlgOpenFile::xml() const
{
    return m_xml;
}

void DlgOpenFile::setXml(const QString &xml)
{
    m_xml = xml;
    settings->setValue("MigrationFile", m_xml);
}

void DlgOpenFile::on_btnGetFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Migration File"), QDir::homePath(), tr("Laycan file (*.xml)"));

    if (!fileName.isEmpty()) {
        ui->edtFile->setText(fileName);
    }
}

void DlgOpenFile::on_btnOpen_clicked()
{
    if (ui->edtFile->text().isEmpty()) {
        QMessageBox::information(this,"","File can't be empty !");
        return;
    }

    this->setXml(ui->edtFile->text());
    this->accept();
}
