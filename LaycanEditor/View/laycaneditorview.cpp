#include "laycaneditorview.h"
#include "ui_laycaneditorview.h"

LaycanEditorView::LaycanEditorView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::laycaneditorview)
{
    ui->setupUi(this);
    m_initialized = false;
}

LaycanEditorView::~LaycanEditorView()
{
    delete ui;
}

void LaycanEditorView::showEvent(QShowEvent *event)
{
    if (m_initialized) return;

    QMainWindow::showEvent(event);
    DlgOpenFile *dlg = new DlgOpenFile;
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->show();

    m_initialized = true;
}
