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

    void setFilePath(const QString);
    QString filePath;
private:

};

#endif // DICTXML_H
