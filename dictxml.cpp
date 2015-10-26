#include <QFile>
#include <QVariant>

#include "dictxml.h"

DictXML::DictXML()
{

}

QVariant DictXML::GetFieldPropertyByName(const QString aName, const QString aProperty)
{
    QDomNodeList nodes = root.elementsByTagName(aName);

    for(int i = 0; i < nodes.count(); i++)
    {
        QDomNode elm = nodes.at(i);
        QDomElement e = elm.toElement();

        Menssage(e.attribute("Name"));

        if (e.attribute("Name") == aName)
        {
            break;
            return e.attribute(aProperty);
        }
    }
    return QVariant::Invalid;
}

void DictXML::InitXML(const QString afilePath)
{
    filePath = afilePath;

    QDomDocument doc;
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        Menssage("Erro ao abrir arquivo XML");

    if (!doc.setContent(&file))
        file.close();

    file.close();
    root = doc.firstChildElement();
}

