#ifndef MYSQL_H
#define MYSQL_H

#include <QVariant>
#include <QVariantMap>


class MySQL
{

private:


public:
    MySQL();
    ~MySQL();
   static QString Exec(QString SQL);
   static QVariant Return(const QString SQL);
   static QString add(const QVariant var);
   static QString addWhere(const QString var);

};

#endif // MYSQL_H
