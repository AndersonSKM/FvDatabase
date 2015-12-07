#include "connection.h";
#include <QMessageBox>
#include <QAbstractButton>
#include <QPushButton>
#include <QApplication>

Database* Database::m_instance = NULL;

Database::Database()
{

}

Database::~Database()
{

}

Database* Database::instance()
{
    if( !m_instance )
        m_instance = new Database();

    return m_instance;
}


bool Database::databaseError()
{
    const QString errorMessage = "O sistema nao encontrou a conecxao com o banco de dados por favor verifique-a e tente novamente";

    QMessageBox *msgBox = new QMessageBox;
    QAbstractButton *cancelButton = msgBox->addButton(tr("Cancelar"), QMessageBox::NoRole);
    QAbstractButton *configButton = msgBox->addButton(tr("Configurar Conecxão"), QMessageBox::YesRole);
    msgBox->setText("Erro ao Conecar a Base de Dados");
    msgBox->setInformativeText(errorMessage);
    msgBox->setIcon(QMessageBox::Critical);
    msgBox->exec();

    if(msgBox->clickedButton() == cancelButton)
        return false;
    else if(msgBox->clickedButton() == configButton)
        return true;

return false;
}

bool Database::setConection(IniFile *parameters)
{
   qDebug() << "[Iniciando conexao]";

   //Cria conexao apartir dos dados passados
   Database::instance()->m_db = QSqlDatabase::addDatabase("QMYSQL");
   Database::instance()->m_db.setHostName( parameters->server() );
   Database::instance()->m_db.setUserName( parameters->userName() );
   Database::instance()->m_db.setPassword( parameters->passwd() );
   Database::instance()->m_db.setPort( parameters->port() );

   if (!Database::instance()->m_db.open())
   {
       qDebug() << "[Conexao falhou:"+Database::instance()->m_db.lastError().text()+"]";
       return false;
   }

   qDebug() << "[Verificando Banco de dados]";

   if (!parameters->database().isEmpty())
   {
       QString query = "SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = '"+parameters->database()+"'";
       QSqlQuery q(query,Database::instance()->m_db);

       if (q.size() == 0)
       {
           qDebug() << "[Criando banco de dados]";

           if (!q.exec("CREATE DATABASE IF NOT EXISTS " + parameters->database() + ";"))
               qDebug() << "[Erro ao criar base de dados: " << q.lastError().text() << "]";
           else
               Database::instance()->m_db.close();
       }
   }

   qDebug() << "[Banco ja existente estabelecendo conexao]";
   Database::instance()->m_db.setDatabaseName(parameters->database());

   if (Database::instance()->m_db.open())
       qDebug() << "[Conexao estabelecida com o banco " << Database::instance()->m_db.databaseName() << "]";

   return true;
}


