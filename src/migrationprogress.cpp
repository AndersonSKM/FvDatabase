#include "migrationprogress.h"
#include "ui_migrationprogress.h"

MigrationProgress::MigrationProgress(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MigrationProgress)
{
    ui->setupUi(this);
}

MigrationProgress::~MigrationProgress()
{
    delete ui;
}

void MigrationProgress::showEvent(QShowEvent *)
{

}

void MigrationProgress::doWork()
{

}
