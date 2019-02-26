#include "Position.h"

#include <QXmlStreamWriter>
#include <QXmlStreamReader>

Position::Position()
{
}

Position::Position(int x, int y, QString name) :
    x(x), y(y), name(name)
{

}

QString Position::toXML()
{
    QString xml;
    QXmlStreamWriter xmlWriter(&xml);

    xmlWriter.writeStartElement("Position");
    xmlWriter.writeTextElement("name", name);
    xmlWriter.writeTextElement("x", QString::number(x));
    xmlWriter.writeTextElement("y", QString::number(y));
    xmlWriter.writeEndElement();

    return xml;
}

Position Position::fromXML(QXmlStreamReader &xmlReader)
{
    Position position;

    xmlReader.readNextStartElement();
    position.name = xmlReader.readElementText();
    xmlReader.readNextStartElement();
    position.x = xmlReader.readElementText().toInt();
    xmlReader.readNextStartElement();
    position.y = xmlReader.readElementText().toInt();

    return position;
}
