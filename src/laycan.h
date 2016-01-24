#ifndef Laycan_H
#define Laycan_H

#include <QDomDocument>

#include "migrationprogress.h"

enum DataTypes {
    ftInteger,
    ftVarchar,
    ftDateTime,
    ftFloat,
    ftBoolean
};

enum IndexType {
    ftPrimary,
    ftKey,
    ftUnique
};

class Fields
{
public:
    explicit Fields(QString name, DataTypes type, int size, bool isNull,
        bool pk, QVariant def, bool autoIncKey);
    explicit Fields() {}
    inline ~Fields() {}

    QString toSQL(void);
    QString typeToSQL(DataTypes type);

    void setName(QString name);
    void setType(DataTypes type);
    void setSize(int size);
    void setIsNull(bool isNull);
    void setPrimaryKey(bool pk);
    void setDefaultValue(QVariant def);
    void setExtra(QString extra);
    void setAutoIncKey(bool autoInc);

    QString name(void);
    DataTypes type(void);
    int size(void);
    bool isNull(void);
    bool isPrimaryKey(void);
    QVariant defaultValue(void);
    QString extra(void);
    bool isAutoIncKey(void);
private:
    QString f_name;
    DataTypes f_type;
    int f_size;
    bool f_null;
    bool f_primaryKey;
    QVariant f_defaultValue;
    QString f_extra;
};

class Index
{
public:
    explicit Index(QString name, IndexType type);
    inline Index() {}
    inline ~Index() {}

    void setName(QString name);
    void setType(IndexType type);

    QString name(void);
    IndexType type(void);
private:
    QString i_name;
    IndexType i_type;
};

class Constraint;

class Table
{
public:
    Table() {}
    ~Table() {}

    Fields fieldByName(QString);

    void setName(QString);
    QString name(void);

    QList<Fields> fields;
    QList<Index> indexes;
    QList<Constraint> constraints;
private:
    QString t_name;
};

class Constraint
{
public:
    explicit Constraint(QString name, Fields column, Table referTable,Fields referColumn) :
        c_name(name), c_column(column), c_referTable(referTable), c_referColumns(referColumn) {}

    /* Generate Name Atomatically */
    explicit Constraint(Table *parent, Fields column, Table referTable,Fields referColumn);

    inline Constraint() {}
    inline ~Constraint() {}

    void setName(QString);
    void setColumn(Fields);
    void setReferTable(Table);
    void setReferColumn(Fields);

    QString name(void);
    Fields column(void);
    Table referTable(void);
    Fields referColumns(void);
private:
    QString c_name;
    Fields c_column;
    Table c_referTable;
    Fields c_referColumns;
};

class Migration
{
public:
    inline Migration() {}
    inline ~Migration() {}

    void setVersion(int);
    void setDescription(QString);
    void setSQL(QString);

    int version(void);
    QString description(void);
    QString SQL(void);
private:
    int m_version;
    QString m_description;
    QString m_sql;
};

class Laycan
{
public:
    explicit Laycan();
    ~Laycan();

    void Migrate(const QString);

    void addTablesChanged(void);
    void addVerifiedTables(void);
    void addCreatedTables(void);

    void setProgressVisible(bool visible);
    void setTablesChanged(int count);
    void setVerifiedTables(int count);
    void setCreatedTables(int count);

    bool progressVisible(void);
    int tablesChanged(void);
    int verifiedTables(void);
    int createTables(void);
private:
    void InitXML(QString);
    void loadTablesFromXML(void);
    void loadMigrationsFromXML(void);
    void executeMigrations(void);

    bool writeMigrationLog(Migration&);

    void compareTables(void);
    void compareFields(Table &);

    Table tableByName(QString);

    QString generateAddColumnSQL(QString tableName, Fields field);
    QString generateSQL(Table &);

    bool columnExists(QString tableName, QString columnName);

    QString filePath;
    QDomDocument xml;

    MigrationProgress *dlg;
    QList<Table> Tables;
    QList<Migration> Migrations;

    bool m_progressVisible;
    int m_tablesChanged;
    int m_verifiedTables;
    int m_createdTables;  
};

#endif // Laycan_H
