#ifndef DATABASECONFIG_H
#define DATABASECONFIG_H

#include <QMainWindow>

#include "inifile.h"
#include "connection.h"

namespace Ui {
  class databaseconfig;
}

class databaseconfig : public QMainWindow
{
    Q_OBJECT

public:
    explicit databaseconfig(QWidget *parent = 0);
    ~databaseconfig();

private slots:
    void on_btnOk_clicked();

    void on_btnCancel_clicked();

private:
    Ui::databaseconfig *ui;
    IniFile *ini;
};

#endif // DATABASECONFIG_H
