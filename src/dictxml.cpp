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

Table DictXML::LoadTable(const QString aName)
{
    Table tb;
    tb.setName(aName);

    QDomDocument doc = InitXML(filePath);
    QDomNodeList root = doc.elementsByTagName("Table");

    for (int i = 0; i != root.count(); i++) {
        QDomNode tableNode = root.at(i);

        if (tableNode.isElement()) {
            QDomElement tableElement = tableNode.toElement();

            if (tableElement.attribute("Name") == aName) {
                QDomNodeList fieldsNodes = tableNode.childNodes();

                for (int i = 0; i != fieldsNodes.count(); i++) {
                    QDomNode fieldNode = fieldsNodes.at(i);

                    if (fieldNode.isElement()) {
                        QDomElement fieldElement = fieldNode.toElement();

                        Fields f;
                        f.setName(fieldElement.attribute("Name"));

                        QString type = fieldElement.attribute("Type");
                        if (type.toUpper() == "INTEGER")
                            f.setType(ftInteger);
                        else if (type.toUpper() == "VARCHAR")
                            f.setType(ftVarchar);
                        else if (type.toUpper() == "BOOLEAN")
                            f.setType(ftBoolean);
                        else if (type.toUpper() == "FLOAT")
                            f.setType(ftFloat);

                        f.setSize(fieldElement.attribute("Size").toInt());
                        f.setIsNull(fieldElement.attribute("Null","1").toInt());
                        f.setPrimaryKey(fieldElement.attribute("Pk","0").toInt());
                        f.setDefaultValue(fieldElement.attribute("Default"));
                        f.setExtra(fieldElement.attribute("Extra"));

                        tb.fields.append(f);
                    }
                } //end for
            }
        }
    }//end for

    return tb;
}

QDomDocument DictXML::InitXML(const QString filePath)
{
    QDomDocument doc;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        Menssage("Erro ao abrir arquivo XML");

    if (!doc.setContent(&file)) {
        file.close();
        Menssage("Erro ao setar XML");
    }

    file.close();

    return doc;
}

