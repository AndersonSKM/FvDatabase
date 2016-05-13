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

    QString xml() const;
    void setXml(const QString &xml);

private slots:
    void on_btnCancel_clicked();
    void on_btnOpen_clicked();
    void on_btnGetFile_clicked();

private:
    QString m_xml;
    QSettings *settings;
    Ui::DlgOpenFile *ui;
};

#endif // DLGOPENFILE_H
