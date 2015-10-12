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
    int m_port = 3306;

    QString m_PATH;

    bool verifyIniFile();
public:
    IniFile(QString PATH);
    drivers driverType();
    QString server();
    QString userName();
    QString passwd();
    int port();

    void setDriverType(drivers);
    void setServer(QString);
    void setUserName(QString);
    void setPasswd(QString);
    void setPort(int);

    void save();
};

#endif // INIFILE_H
