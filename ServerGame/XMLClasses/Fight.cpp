#include "Fight.h"

#include <QXmlStreamWriter>
#include <QXmlStreamReader>

Fight::Fight()
{
}

Fight::Fight(QString name1, QString name2, bool isInsert) :
    name1(name1), name2(name2), isInsert(isInsert)
{
}

QString Fight::toXML()
{
    QString xml;
    QXmlStreamWriter xmlWriter(&xml);

    xmlWriter.writeStartElement("Fight");
    xmlWriter.writeTextElement("name1", name1);
    xmlWriter.writeTextElement("name2", name2);
    xmlWriter.writeTextElement("isInsert", QString::number(isInsert));
    xmlWriter.writeEndElement();

    return xml;
}

Fight Fight::fromXML(QXmlStreamReader &xmlReader)
{
    Fight fight;

    xmlReader.readNextStartElement();
    fight.name1 = xmlReader.readElementText();
    xmlReader.readNextStartElement();
    fight.name2 = xmlReader.readElementText();
    xmlReader.readNextStartElement();
    fight.isInsert = xmlReader.readElementText().toInt();

    return fight;
}
