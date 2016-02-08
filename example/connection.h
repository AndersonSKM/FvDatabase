#ifndef CONNECTION_H
#define CONNECTION_H

#include <QWidget>
#include <QFile>
#include <QtSql>
#include <QMessageBox>

#include "inifile.h"

class Database : public QWidget
{
public:
    Database();
    ~Database();

    static void Menssage(QString text);

    bool setConection(IniFile *parameters);
    bool databaseError(QString erro);
private:
   QSqlDatabase db;
};


#endif // Connection_H
