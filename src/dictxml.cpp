#include <QFile>
#include <QVariant>
#include <QDebug>


#include "dictionary.h"
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
    return 0;
}

QVariant DictXML::getTablePropertyByName(const QString aName, const QString aProperty)
{
    QDomNodeList tablesNodes = InitXML(filePath,"Table");

    for (int i = 0; i != tablesNodes.count(); i++)
    {
        QDomNode tableNode = tablesNodes.at(i);
        if (tableNode.isElement())
        {
            QDomElement tableElement = tableNode.toElement();
            if (tableElement.attribute("Name").toUpper() == aName.toUpper())
            {
                return tableElement.attribute(aProperty);
                break;
            }
        }
    }
    return 0;
}

Table DictXML::LoadTable(const QString aName)
{
    Table tb;
    tb.setName(aName);

    QDomNodeList fieldsNodes = InitXML(filePath,"Field");

    for (int i = 0; i != fieldsNodes.count(); i++)
    {
        QDomNode fieldNode = fieldsNodes.at(i);
        if (fieldNode.isElement())
        {
            QDomElement fieldElement = fieldNode.toElement();

            Fields f;
            QString fieldName = fieldElement.attribute("Name");
            QString type = getFieldPropertyByName(fieldName, "Type").toString();

            f.setName(fieldName);

            if (type.toUpper() == "INTEGER")
                f.setType(ftInteger);
            else if (type.toUpper() == "VARCHAR")
                f.setType(ftVarchar);
            else if (type.toUpper() == "BOOLEAN")
                f.setType(ftBoolean);

            f.setSize( getFieldPropertyByName(fieldName, "Size").toInt() );
            f.setPrimaryKey( getFieldPropertyByName(fieldName, "Pk").toBool() );
            f.setDefaultValue(getFieldPropertyByName(fieldName, "DEFAULT") );

            tb.fields.append(f);
        }
    }
    return tb;
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

