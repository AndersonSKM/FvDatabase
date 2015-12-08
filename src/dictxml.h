#ifndef DICTXML_H
#define DICTXML_H

#include <QVariant>
#include <QDomDocument>

#include "lib/tools.h"
#include "dictionary.h"

class Table;

class DictXML
{
public:
    DictXML();
    QDomNodeList InitXML(const QString filePath, const QString nodeName);
    QVariant getFieldPropertyByName(const QString aName, const QString aProperty);
    QVariant getTablePropertyByName(const QString aName, const QString aProperty);

    Table LoadTable(const QString aName);
    
    void setFilePath(const QString);
    QString filePath;
private:

};

#endif // DICTXML_H
