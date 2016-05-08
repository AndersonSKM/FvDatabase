#include "laycaneditorview.h"
#include "ui_laycaneditorview.h"

#include <QtXml>

LaycanEditorView::LaycanEditorView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::laycaneditorview)
{
    ui->setupUi(this);
    m_initialized = false;

    //Create a model
    model = new QStandardItemModel(0,2,this);
    model->setHeaderData(0,Qt::Horizontal,"Verison");
    model->setHeaderData(1,Qt::Horizontal,"Description");
}

LaycanEditorView::~LaycanEditorView()
{
    delete ui;
    delete model;
}

void LaycanEditorView::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
    if (m_initialized) return;

    //Create a dialog to get Migration file
    DlgOpenFile dlg;
    if (dlg.exec() == QDialog::Rejected) {
        this->close();
    }

    QDomDocument document = dlg.getXml();
    parseXml(document);

    ui->treeMigrations->setModel(model);
    ui->treeMigrations->sortByColumn(0,Qt::AscendingOrder);
    ui->treeMigrations->expandAll();
    m_initialized = true;
}

void LaycanEditorView::parseXml(QDomDocument &xml)
{
    QStandardItem *root = new QStandardItem("Migrations");
    model->appendRow(root);

    //Get the xml root element
    QDomElement xmlRoot = xml.firstChildElement();

    //Read migrations
    QDomNodeList migrations = xmlRoot.elementsByTagName("Migration");
    for (auto i = 0; i < migrations.count(); i++) {
        QDomElement migration =  migrations.at(i).toElement();

        //Add item
        QList<QStandardItem*> items;
        items.append(new QStandardItem(migration.attribute("version")));
        items.append(new QStandardItem(migration.attribute("id","Update version")));
        root->appendRow(items);
    }
}

bool LaycanEditorView::isInitialized() const
{
    return m_initialized;
}

void LaycanEditorView::setInitialized(bool initialized)
{
    m_initialized = initialized;
}

