#ifndef LAYCANEDITORVIEW_H
#define LAYCANEDITORVIEW_H

#include <QMainWindow>
#include <QShowEvent>

#include "dlgopenfile.h"

namespace Ui {
class laycaneditorview;
}

class LaycanEditorView : public QMainWindow
{
    Q_OBJECT

public:
    explicit LaycanEditorView(QWidget *parent = 0);
    ~LaycanEditorView();

public slots:
    void showEvent(QShowEvent* event);

private:
    Ui::laycaneditorview *ui;
    bool m_initialized;
};

#endif // LAYCANEDITORVIEW_H
