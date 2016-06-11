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
#include "SQLHighlighter.h"

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
    void on_btnSave_clicked();
    void on_btnNew_clicked();

    void on_btnDelete_clicked();

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private:
    void writeFile();

    void read(const QJsonObject &json);
    void write(const QJsonObject &json);

    void abort(const QString &msg = "");
    void setEditsEnabled(const bool value);
    void setActionsButtonsEnabled(const bool value, const bool onlyNew = false);
    void setEditButtonsEnabled(const bool value);
    void setupEditors();

    bool m_initialized;
    QModelIndex m_currentIndex;
    EditorModes m_mode;
    QString m_jsonFileName;
    QStandardItemModel *model;
    QStandardItem *root;
    Ui::laycaneditorview *ui;
    SQLHighlighter *highlighterUp;
    SQLHighlighter *highlighterDown;
};

#endif // LAYCANEDITORVIEW_H
