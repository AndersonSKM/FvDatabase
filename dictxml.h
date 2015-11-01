#ifndef DICTXML_H
#define DICTXML_H

#include <QVariant>
#include <QDomDocument>


#include "tools/tools.h"

class DictXML
{
public:
    DictXML();
    void GetFieldPropertyByName(const QString aName, const QString aProperty);
    
    void InitXML(const QString afilePath);

private:
    QString filePath; 
    
};

#endif // DICTXML_H
