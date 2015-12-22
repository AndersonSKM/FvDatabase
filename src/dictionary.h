#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QDialog>
#include <QList>
#include <QVariant>
#include <QSqlDatabase>

#include "dictxml.h"
#include "migrationprogress.h"

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

    QString toSQL(void);
    QString typeToSQL(DataTypes type);

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
    explicit Dictionary();
    ~Dictionary();

    void Migrate(const QString);
    void compareTables(void);

    QString generateSQL(Table &);
    bool createTables();

    void setProgressVisible(bool visible);
    bool progressVisible(void);
private:
    void loadTablesFromFile(const QString &);
    void compareFields(Table &);

    QString generateAddColumnSQL(QString tableName, Fields field);
    //QString generateAddColumnSQL(QString &tableName, Fields &field, QList<Fields>);

    bool columnExists(QString tableName, QString columnName);

    MigrationProgress *dlg;
    QList<Table> Tables;
    bool m_progressVisible;
};

#endif // DICTIONARY_H
