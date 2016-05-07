#ifndef LAYCANEDITORVIEW_H
#define LAYCANEDITORVIEW_H

#include <QtCore>
#include <QWidget>
#include <QtGui>
#include <QStandardItemModel>
#include <QMainWindow>
#include <QShowEvent>
#include <QtXml>
#include <QMessageBox>

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

    bool isInitialized() const;
    void setInitialized(bool initialized);

public slots:
    void showEvent(QShowEvent* event);

private:
    void parseXml(QDomDocument &xml);

    QStandardItemModel *model;
    Ui::laycaneditorview *ui;
    bool m_initialized;
};

#endif // LAYCANEDITORVIEW_H
