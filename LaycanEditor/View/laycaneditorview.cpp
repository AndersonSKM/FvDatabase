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
        abort();
        return;
    }

    m_xmlFile.setFileName(dlg.xml());
    if (!m_xmlFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        abort(m_xmlFile.errorString());
        return;
    }

    QDomDocument document;
    if (!document.setContent(&m_xmlFile)) {
        m_xmlFile.close();
        abort("Invalid XML file");
        return;
    }

    readFile(document);

    ui->treeMigrations->setModel(model);
    ui->treeMigrations->sortByColumn(0,Qt::AscendingOrder);
    ui->treeMigrations->expandAll();
    ui->treeMigrations->header()->resizeSection(0,85);
    m_initialized = true;
}

void LaycanEditorView::writeFile()
{
  //Save changes on the disk
}

void LaycanEditorView::abort(const QString &msg)
{
    this->close();
    if (!msg.isEmpty()) {
        QMessageBox::critical(this,"Error",msg);
    }
}

void LaycanEditorView::readFile(const QDomDocument &document)
{
    //Parse Xml File

    QStandardItem *root = new QStandardItem("Migrations");
    model->appendRow(root);

    //Get the xml root element
    QDomElement xmlRoot = document.firstChildElement();

    //Read all migrations
    QDomNodeList migrations = xmlRoot.elementsByTagName("Migration");
    for (auto i = 0; i < migrations.count(); i++) {
        QDomElement migration =  migrations.at(i).toElement();

        //Add all propertys of migration in one item
        QList<QStandardItem*> items;
        items.append(new QStandardItem(migration.attribute("version")));
        items.append(new QStandardItem(migration.attribute("id","Update version")));

        QDomNodeList scripts;

        scripts = migration.elementsByTagName("UpVersion");
        for (auto j = 0; j < scripts.count(); j++) {
            QDomElement upVersion = scripts.at(j).toElement();

            //SQL UpVersion in Comment Node
            if (upVersion.nodeType() == 8) {
                 items.append(new QStandardItem(upVersion.nodeValue()));
            }
        }

        scripts = migration.elementsByTagName("DownVersion");
        for (auto h = 0; h < scripts.count(); h++) {
            QDomElement downVersion = scripts.at(h).toElement();

            //SQL DownVersion in Comment Node
            if (downVersion.nodeType() == 8) {
                 items.append(new QStandardItem(downVersion.nodeValue()));
            }
        }

        //Append row in all migrations
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

