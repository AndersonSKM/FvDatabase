#include "migrationprogress.h"
#include "ui_migrationprogress.h"

MigrationProgress::MigrationProgress(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MigrationProgress)
{
    ui->setupUi(this);
    ui->progressBar->setValue(0);
    ui->lbStatus->setText("");
}

MigrationProgress::~MigrationProgress()
{
    delete ui;
}

void MigrationProgress::setProgress(int value)
{
    ui->progressBar->setValue(value);
}

void MigrationProgress::setMaximum(int value)
{
    ui->progressBar->setMaximum(value);
}

void MigrationProgress::setStatus(QString value, QString color)
{
    ui->lbStatus->setText("<font color='"+color+"'>"+value+"</font>");
}

void MigrationProgress::update()
{
    ui->progressBar->update();
    ui->label->update();
}
