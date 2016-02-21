#ifndef CONNECTION_H
#define CONNECTION_H

#include <QWidget>
#include <QFile>
#include <QtSql>
#include <QMessageBox>

class Database : public QWidget
{
public:
    Database();
    ~Database();

    static void Menssage(QString text);

    bool setConection(void);
    void databaseError(const QString);
private:
   QSqlDatabase db;
};


#endif // Connection_H
