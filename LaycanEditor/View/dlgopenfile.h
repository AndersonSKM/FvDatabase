#ifndef DLGOPENFILE_H
#define DLGOPENFILE_H

#include <QDialog>
#include <QSettings>
#include <QtXml>

namespace Ui {
class DlgOpenFile;
}

class DlgOpenFile : public QDialog
{
    Q_OBJECT

public:
    explicit DlgOpenFile(QWidget *parent = 0);
    ~DlgOpenFile();

    QDomDocument getXml();
    void setXml(const QDomDocument xml);

public slots:
    void closeEvent(QCloseEvent *event);

signals:
    void dialogResult(const bool value);

private slots:
    void on_btnCancel_clicked();

    void on_pushButton_clicked();

    void on_btnOpen_clicked();

private:
    QDomDocument m_xml;
    QSettings *settings;
    Ui::DlgOpenFile *ui;
};

#endif // DLGOPENFILE_H
