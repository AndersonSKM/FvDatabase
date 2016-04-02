#ifndef LAYCANEDITOR_H
#define LAYCANEDITOR_H

#include <QMainWindow>

namespace Ui {
class LaycanEditor;
}

class LaycanEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit LaycanEditor(QWidget *parent = 0);
    ~LaycanEditor();

private slots:
    void on_btnClose_clicked();

private:
    Ui::LaycanEditor *ui;
};

#endif // LAYCANEDITOR_H
