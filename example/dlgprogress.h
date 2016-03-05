#ifndef DLGPROGRESS_H
#define DLGPROGRESS_H

#include <QDialog>
#include <QLabel>

namespace Ui {
class DlgProgress;
}

class DlgProgress : public QDialog
{
    Q_OBJECT

public:
    explicit DlgProgress(QWidget *parent = 0);
    ~DlgProgress();

    QLabel* status(void);
    QTextBrowser out(void);

private slots:
    void on_btnOk_clicked();

private:
    Ui::DlgProgress *ui;
};

#endif // DLGPROGRESS_H
