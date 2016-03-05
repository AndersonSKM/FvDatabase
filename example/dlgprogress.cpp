#include "dlgprogress.h"
#include "ui_dlgprogress.h"
#include "mainwindow.h"

DlgProgress::DlgProgress(QWidget *parent, Laycan *l) :
    QDialog(parent),
    ui(new Ui::DlgProgress),
    laycan(l)
{
    ui->setupUi(this);
    isInitialized = false;
}

DlgProgress::~DlgProgress()
{
    delete ui;
}

void DlgProgress::on_btnOk_clicked()
{
    MainWindow *m = new MainWindow;
    m->setAttribute(Qt::WA_DeleteOnClose);
    m->showMaximized();
    this->close();
}

void DlgProgress::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event);
    if (event->spontaneous())
        return;

    if (isInitialized)
        return;

    this->update();
    QApplication::processEvents();
    laycan->setOutStatus(ui->lbStatus);
    laycan->setOutTextLog(ui->memoLog);
    startMigration(":/Migrations.xml");

    isInitialized = true;
}

void DlgProgress::startMigration(const QString& xmlPath)
{
    laycan->Migrate(xmlPath);
}
