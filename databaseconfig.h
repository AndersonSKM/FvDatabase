#ifndef DATABASECONFIG_H
#define DATABASECONFIG_H

#include <QDialog>
#include <QDomElement>

#include "inifile.h"

namespace Ui {
class DatabaseConfig;
}

class DatabaseConfig : public QDialog
{
    Q_OBJECT

public:
    explicit DatabaseConfig(QWidget *parent = 0);
    ~DatabaseConfig();

private slots:
    void on_btnOk_clicked();

    void on_btnCancel_clicked();

private:
    Ui::DatabaseConfig *ui;
    IniFile *ini;
};

#endif // DATABASECONFIG_H
