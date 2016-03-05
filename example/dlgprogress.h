#ifndef DLGPROGRESS_H
#define DLGPROGRESS_H

#include <QDialog>
#include <QLabel>
#include <QShowEvent>

#include "laycan.h"

namespace Ui {
class DlgProgress;
}

class DlgProgress : public QDialog
{
    Q_OBJECT

public:
    explicit DlgProgress(QWidget *parent = 0, Laycan *l = nullptr);
    ~DlgProgress();
    void startMigration(const QString &xmlPath);

private slots:
    void on_btnOk_clicked();
    void showEvent(QShowEvent *event);

private:
    Ui::DlgProgress *ui;
    Laycan *laycan;
    bool isInitialized;
};

#endif // DLGPROGRESS_H
