#ifndef CONNECTION_H
#define CONNECTION_H

#include <QWidget>
#include <QFile>
#include <QtSql>
#include <QMessageBox>

#include "inifile.h"

class Database : public QWidget
{
    Q_OBJECT
public:
    Database();
    ~Database();

    bool setConection(IniFile *parameters);
    bool databaseError(QString erro);
signals:

public slots:

private:
   QSqlDatabase db;
};


#endif // Connection_H
