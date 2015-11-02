#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QList>
#include <QVariant>

#include <dictxml.h>

enum DataTypes {
    ftInteger,
    ftVarchar,
    ftDateTime,
    ftFloat,
    ftBoolean
};

class Fields
{
public:
    explicit Fields(QString name, DataTypes type, int size, bool pk, QVariant def);
    explicit Fields() {}
    ~Fields();
    void setName(QString name);
    void setType(DataTypes type);
    void setSize(int size);
    void setPrimaryKey(bool pk);
    void setDefaultValue(QVariant def);

    QString name(void);
    DataTypes type(void);
    int size(void);
    bool isPrimaryKey(void);
    QVariant defaultValue(void);
private:
    QString f_name;
    DataTypes f_type;
    int f_size;
    bool f_primaryKey;
    QVariant f_defaultValue;
};

class Table
{
public:
    Table() {}
    ~Table() {}

    void setName(QString);

    QString name(void);

    QList<Fields> fields;
private:
    QString t_name;
};

class Dictionary
{
public:
    Dictionary();
    QString generateSQL(Table &);
    bool createTables();

    void loadTablesFromFile(const QString &filePath);

private:
    QList<Table> Tables;
};

#endif // DICTIONARY_H
