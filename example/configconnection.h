#ifndef CONFIGCONNECTION_H
#define CONFIGCONNECTION_H

#include <QDialog>

#include "laycan.h"

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
    void updateOutput(QString msg, LogLevel l);

public slots:
    void closeEvent();

private:
    void loadSettings(void);
    void writeSettings(void);

    Laycan *laycan;

    Ui::ConfigConnection *ui;
};

#endif // CONFIGCONNECTION_H
