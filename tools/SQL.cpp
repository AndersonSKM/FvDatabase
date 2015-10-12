#include "sql.h"
#include "QtSql/QSqlQuery"
#include <QMessageBox>
#include <QSqlError>

MySQL::MySQL()
{

}

QString MySQL::Exec(const QString SQL)
{
    QSqlQuery query;
    if ( !query.exec(SQL) )
        QMessageBox::information(NULL,"",query.lastError().text());
}

QVariant MySQL::Return(const QString SQL)
{
    QSqlQuery query;

    query.prepare(SQL);

    if (query.exec())
    {
        query.next();
        if (query.value(0).isNull())
            return QVariant::Invalid;
        else
            return query.value(0);
    }
    else
        QMessageBox::information(NULL,"",query.lastError().text());

}

QString MySQL::add(const QVariant var)
{
    return var.toString();
}

