#include <QFile>
#include <QVariant>
#include <QDebug>

#include "dictxml.h"

DictXML::DictXML()
{

}

void DictXML::setFilePath(const QString path)
{
    filePath = path;
}

QVariant DictXML::getFieldPropertyByName(const QString aName, const QString aProperty)
{
    QDomNodeList fieldNodes = InitXML(filePath,"Field");

    if (!fieldNodes.isEmpty())
    {
        for (int i = 0; i != fieldNodes.count(); i++)
        {
            QDomNode tableNode = fieldNodes.at(i);

            if (tableNode.isElement())
            {
                QDomElement fieldElement = tableNode.toElement();

                if (fieldElement.attribute("Name").toUpper() == aName.toUpper())
                {
                    return fieldElement.attribute(aProperty);
                    break;
                }
            }
        }
    }
}

QDomNodeList DictXML::InitXML(const QString filePath, const QString nodeName = "Tables")
{
    QDomDocument doc;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        Menssage("Erro ao abrir arquivo XML");

    qDebug() << "[Carregando arquivo " << filePath << "]";

    if (!doc.setContent(&file)) {
        file.close();
        Menssage("Erro ao setar XML");
    }

    file.close();
    qDebug() << "[Fechando arquivo]";

    QDomElement root = doc.firstChildElement();
    return root.elementsByTagName(nodeName);
}

