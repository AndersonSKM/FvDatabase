#ifndef MIGRATION_H
#define MIGRATION_H

#include <QString>

class Migration
{
public:
    inline Migration() {}
    inline ~Migration() {}

    float version(void);
    void setVersion(float);

    QString description(void);
    void setDescription(QString);

    int executionTime() const;
    void setExecutionTime(int executionTime);

    QString DownSql() const;
    void setDownSql(const QString &DownSql);

    QString UpSql() const;
    void setUpSql(const QString &UpSql);

private:
    float m_version;
    QString m_description;
    QString m_UpSql;
    QString m_DownSql;
    int m_executionTime;
};

#endif // MIGRATION_H
