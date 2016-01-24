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

bool Database::databaseError(QString erro)
{
    const QString errorMessage = "O sistema não consegiu se conectar com o banco de dados"
                                 " por favor verifique-a o erro: "+erro;
    QMessageBox *msgBox = new QMessageBox;
    QAbstractButton *configButton = msgBox->addButton(tr("Configurar Conecxão"), QMessageBox::YesRole);
    msgBox->addButton(tr("Cancelar"), QMessageBox::NoRole);
    msgBox->setText("Erro ao Conecar a Base de Dados");
    msgBox->setInformativeText(errorMessage);
    msgBox->setIcon(QMessageBox::Critical);
    msgBox->exec();

    if(msgBox->clickedButton() == configButton)
        return true;

return false;
}

bool Database::setConection(IniFile *parameters)
{
   qDebug() << "[Iniciando conexao]";

   //Cria conexao apartir dos dados passados
   db = QSqlDatabase::addDatabase("QMYSQL");
   db.setHostName( parameters->server() );
   db.setUserName( parameters->userName()) ;
   db.setPassword( parameters->passwd() );
   db.setDatabaseName( parameters->database() );
   db.setPort( parameters->port() );

   qDebug() << "[Verificando Banco de dados]";
   if (!db.open()) {
       qDebug() << "[Conexao falhou:"+db.lastError().text()+"]";
       databaseError(db.lastError().text());
       return false;
   }

   qDebug() << "[Conexao estabelecida com o banco " << db.databaseName() << "]";
   return true;
}
