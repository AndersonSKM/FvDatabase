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

void LaycanEditor::filterList()
{

}
QDomDocument LaycanEditor::xml() const
{
    return m_xml;
}

void LaycanEditor::setXml(const QDomDocument &xml)
{
    m_xml = xml;
}



