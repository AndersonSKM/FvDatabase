#ifndef DICTXML_H
#define DICTXML_H

#include <QVariant>
#include <QDomDocument>


#include "tools/tools.h"

class DictXML
{
public:
    DictXML();
    QDomNodeList InitXML(const QString filePath, const QString nodeName);
    QVariant getFieldPropertyByName(const QString aName, const QString aProperty);
    
    void setFilePath(const QString);

private:
    QString filePath; 
    
};

#endif // DICTXML_H
