#include <QMessageBox>
#include <QAbstractButton>
#include <QPushButton>
#include <QApplication>

#include "connection.h"

void Database::Menssage(QString text)
{
    QMessageBox::information(NULL,"",text);
}

Database::Database()
{

}

Database::~Database()
{

}

void Database::databaseError(const QString erro)
{
    QString errorMessage = "The application was unable to connect to database, "
                           "please check the error connection: "+erro;

    QMessageBox::critical(this,"Error connecting to database: ",errorMessage);
}

bool Database::setConection()
{
   qDebug() << "[Starting connection]";

   QSettings setttings("Laycan","LaycanExemple");
   setttings.beginGroup("CONNECTION");

   db = QSqlDatabase::addDatabase("QMYSQL");
   db.setHostName(setttings.value("Server").toString());
   db.setUserName(setttings.value("User").toString()) ;
   db.setPassword(setttings.value("Passwd").toString());
   db.setDatabaseName(setttings.value("Database").toString());
   db.setPort(setttings.value("Port").toInt());
   setttings.endGroup();

   qDebug() << "[Validating connection]";
   if (!db.open()) {
       databaseError(db.lastError().text());
       return false;
   }

   qDebug() << "[Established connection with " << db.databaseName() << "database]";
   return true;
}
