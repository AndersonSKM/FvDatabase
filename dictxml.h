#ifndef DICTXML_H
#define DICTXML_H

#include <QVariant>
#include <QDomDocument>


#include "tools/tools.h"

class DictXML
{
public:
    DictXML();
    QVariant GetFieldPropertyByName(const QString aName, const QString aProperty);
    
    void InitXML(const QString afilePath);

private:
    QString filePath; 
    QDomElement root;
    
};

#endif // DICTXML_H
