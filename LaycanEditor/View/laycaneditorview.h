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

enum EditorModes {
    New  = 1,
    Edit = 2,
    View = 3,
};

class LaycanEditorView : public QMainWindow
{
    Q_OBJECT

public:
    explicit LaycanEditorView(QWidget *parent = 0);
    ~LaycanEditorView();

    bool isInitialized() const;
    void setInitialized(bool initialized);

    EditorModes mode() const;
    void setMode(const EditorModes &mode);

public slots:
    void showEvent(QShowEvent* event);

private slots:
    void on_treeMigrations_clicked(const QModelIndex &index);

    void on_btnEdit_clicked();

    void on_btnCancel_clicked();

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private:
    void readFile(const QDomDocument &document);
    void writeFile();
    void abort(const QString &msg = "");
    void setEditsEnabled(const bool value);
    void setActionsButtonsEnabled(const bool value);
    void setEditButtonsEnabled(const bool value);

    bool m_initialized;
    EditorModes m_mode;
    QFile m_xmlFile;
    QStandardItemModel *model;
    Ui::laycaneditorview *ui;
};

#endif // LAYCANEDITORVIEW_H
