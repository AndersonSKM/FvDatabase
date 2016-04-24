#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class LaycanEditorView : public QDialog
{
    Q_OBJECT

public:
    explicit LaycanEditorView(QWidget *parent = 0);
    ~LaycanEditorView();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
