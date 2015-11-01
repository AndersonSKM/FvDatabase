#include <QFile>
#include <QVariant>
#include <QDebug>

#include "dictxml.h"

DictXML::DictXML()
{

}

void DictXML::GetFieldPropertyByName(const QString aName, const QString aProperty)
{
    QString Path = ":/Migrations/note.xml";

    QDomDocument doc;

    QFile file(Path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        Menssage("Erro ao abrir arquivo XML");

    if (!doc.setContent(&file)) {
        file.close();
        Menssage("Erro ao setar XML");
    }

    file.close();

    QDomElement root = doc.firstChildElement();

    QDomNodeList tableNodes = root.elementsByTagName("Field");

    if (tableNodes.isEmpty())
        qDebug() << "1";

    for (int i = 0; i != tableNodes.count(); i++) {

        //Table
        QDomNode tableNode = tableNodes.at(i);

        QDomElement fieldElement = tableNode.toElement();

        //Fields
        //QDomElement fieldElement = tableNode.firstChildElement("Field");

        qDebug() << fieldElement.attribute(aProperty);

    }
}

void DictXML::InitXML(const QString afilePath)
{

}

