#include "laycaneditorview.h"
#include "ui_laycaneditorview.h"

LaycanEditorView::LaycanEditorView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::laycaneditorview)
{
    ui->setupUi(this);
    m_initialized = false;

    //Create a model
    model = new QStandardItemModel(0,1,this);
}

LaycanEditorView::~LaycanEditorView()
{
    delete ui;
    delete model;
}

void LaycanEditorView::showEvent(QShowEvent *event)
{
    if (m_initialized) return;

    QMainWindow::showEvent(event);

    //Create a dialog to get Migration file
    DlgOpenFile *dlg = new DlgOpenFile;
    dlg->setAttribute(Qt::WA_DeleteOnClose);

    QDomDocument document;
    if (dlg->exec() == QDialog::Accepted) {
        document = dlg->getXml();
    } else {
        this->close();
    }

    parseXml(document);

    ui->treeMigrations->setModel(model);

    m_initialized = true;
}

void LaycanEditorView::parseXml(QDomDocument &xml)
{
    QStandardItem *root = new QStandardItem("Migrations");
    model->appendRow(root);
}

bool LaycanEditorView::isInitialized() const
{
    return m_initialized;
}

void LaycanEditorView::setInitialized(bool initialized)
{
    m_initialized = initialized;
}

