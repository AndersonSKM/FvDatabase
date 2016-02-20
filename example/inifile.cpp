#include <QDir>
#include <QSettings>
#include <QDebug>

#include "inifile.h"

IniFile::IniFile(QString PATH)
{
    m_PATH = PATH;
    m_port = 3306;

    if (verifyIniFile()) {
        QSettings settings(PATH,QSettings::IniFormat);
        settings.beginGroup("CONEXAO");
        m_driverType = mysql;
        m_server = settings.value("SERVER").toString();
        m_userName = settings.value("USERNAME").toString();
        m_passwd = settings.value("PASSWD").toString();
        m_database = settings.value("DATABASE").toString();
        m_port = settings.value("PORT").toInt();
        m_logFilePath = settings.value("LOGFILE").toString();
    }
}

drivers IniFile::driverType()
{
    return m_driverType;
}

QString IniFile::server()
{
    return m_server;
}

QString IniFile::userName()
{
    return m_userName;
}

QString IniFile::passwd()
{
    return m_passwd;
}

QString IniFile::database()
{
    return m_database;
}

int IniFile::port()
{
    return m_port;
}

QString IniFile::logFilePath()
{
    return m_logFilePath;
}

void IniFile::setDriverType(drivers value)
{
    m_driverType = value;
}

void IniFile::setServer(QString value)
{
    m_server = value;
}

void IniFile::setUserName(QString value)
{
    m_userName = value;
}

void IniFile::setPasswd(QString value)
{
    m_passwd = value;
}

void IniFile::setDatabase(QString value)
{
    m_database = value;
}

void IniFile::setPort(int value)
{
    m_port = value;
}

void IniFile::setLogFilePath(QString value)
{
    m_logFilePath = value;
}

bool IniFile::verifyIniFile()
{
    qDebug() << "[Verificando arquivo .ini]";

    QFile iniFile(m_PATH);
    if(!iniFile.exists()) {
       qDebug() << "[Arquivo .ini nao encontrado]";
       return false;
    }

    return true;
}

void IniFile::save()
{
    QSettings settings(m_PATH,QSettings::IniFormat);
    settings.setValue("CONEXAO/DRIVER",   m_driverType == mysql ? "MYSQL" : "OTHER");
    settings.setValue("CONEXAO/SERVER",   m_server);
    settings.setValue("CONEXAO/USERNAME", m_userName);
    settings.setValue("CONEXAO/PASSWD",   m_passwd);
    settings.setValue("CONEXAO/DATABASE", m_database);
    settings.setValue("CONEXAO/PORT",     m_port);
    settings.setValue("CONEXAO/LOGFILE",  m_logFilePath);
    settings.sync();
    qDebug() << "[Salvando em arquivo .ini]";
}
