#include "dlgprogress.h"
#include "ui_dlgprogress.h"

DlgProgress::DlgProgress(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgProgress)
{
    ui->setupUi(this);
}

DlgProgress::~DlgProgress()
{
    delete ui;
}

void DlgProgress::on_btnOk_clicked()
{
    this->setResult(QDialog::Accepted);
    this->close();
}
