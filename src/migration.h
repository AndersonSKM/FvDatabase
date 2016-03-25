#ifndef MIGRATION_H
#define MIGRATION_H

#include <QString>
#include <QDomDocument>

class Migration
{
public:
    inline Migration() {}
    inline ~Migration() {}

    void setVersion(float);
    void setDescription(QString);
    void setSQL(QString);

    float version(void);
    QString description(void);
    QString SQL(void);
    int executionTime() const;
    void setExecutionTime(int executionTime);

private:
    float m_version;
    QString m_description;
    QString m_sql;
    int m_executionTime;
};

#endif // MIGRATION_H
