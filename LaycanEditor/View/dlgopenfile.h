#ifndef DLGOPENFILE_H
#define DLGOPENFILE_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class DlgOpenFile;
}

class DlgOpenFile : public QDialog
{
    Q_OBJECT

public:
    explicit DlgOpenFile(QWidget *parent = 0);
    ~DlgOpenFile();

public slots:
    void closeEvent();

private slots:
    void on_btnCancel_clicked();

    void on_pushButton_clicked();

    void on_btnOpen_clicked();

private:
    QSettings *settings;
    Ui::DlgOpenFile *ui;
};

#endif // DLGOPENFILE_H
