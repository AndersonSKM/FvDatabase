#ifndef CONNECTION_H
#define CONNECTION_H

#include <QWidget>
#include <QFile>
#include <QtSql>
#include <QMessageBox>

class Database : public QWidget
{
    Q_OBJECT
public:
    static Database* instance();
    bool setConection(QStringList parameters);
    bool databaseError(void);
    QSqlDatabase m_db;
signals:

public slots:

private:
    Database();
    ~Database();
    static Database* m_instance;
};


#endif // Connection_H
