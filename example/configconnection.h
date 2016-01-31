#ifndef CONFIGCONNECTION_H
#define CONFIGCONNECTION_H

#include <QDialog>
#include "inifile.h"

namespace Ui {
class ConfigConnection;
}

class ConfigConnection : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigConnection(QWidget *parent = 0);
    ~ConfigConnection();

private slots:
    void on_btnOk_clicked();

    void on_btnCancel_clicked();

private:
    Ui::ConfigConnection *ui;
    IniFile *ini;
};

#endif // CONFIGCONNECTION_H
