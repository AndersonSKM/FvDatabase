#include "laycaneditor.h"
#include "ui_laycaneditor.h"

LaycanEditor::LaycanEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LaycanEditor)
{
    ui->setupUi(this);
}

LaycanEditor::~LaycanEditor()
{
    delete ui;
}

void LaycanEditor::on_btnClose_clicked()
{
    this->close();
}
