#ifndef INIFILE_H
#define INIFILE_H
#include <QString>

enum drivers {
    mysql
};

class IniFile
{
private:
    drivers m_driverType;
    QString m_server;
    QString m_userName;
    QString m_passwd;
    QString m_database;
    int m_port;
    QString m_logFilePath;

    QString m_PATH;

    bool verifyIniFile();
public:
    IniFile(QString PATH);
    drivers driverType();
    QString server();
    QString userName();
    QString passwd();
    QString database();
    int port();
    QString logFilePath();

    void setDriverType(drivers);
    void setServer(QString);
    void setUserName(QString);
    void setPasswd(QString);
    void setDatabase(QString);
    void setPort(int);
    void setLogFilePath(QString);

    void save();
};

#endif // INIFILE_H
