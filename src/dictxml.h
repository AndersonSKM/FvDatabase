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
    QDomDocument InitXML(const QString filePath);
    Table LoadTable(const QString aName);
    
    void setFilePath(const QString);
    QString filePath;
private:

};

#endif // DICTXML_H
