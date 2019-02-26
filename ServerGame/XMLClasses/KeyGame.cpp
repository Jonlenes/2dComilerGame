#include "KeyGame.h"

#include <QXmlStreamWriter>
#include <QXmlStreamReader>

KeyGame::KeyGame()
{
}

KeyGame::KeyGame(QString name, int key) :
    name(name), key(key)
{

}

QString KeyGame::toXML()
{
    QString xml;
    QXmlStreamWriter xmlWriter(&xml);

    xmlWriter.writeStartElement("KeyGame");
    xmlWriter.writeTextElement("name", name);
    xmlWriter.writeTextElement("key", QString::number(key));
    xmlWriter.writeEndElement();

    return xml;
}

KeyGame KeyGame::fromXML(QXmlStreamReader &xmlReader)
{
    KeyGame keyGame;

    xmlReader.readNextStartElement();
    keyGame.name = xmlReader.readElementText();
    xmlReader.readNextStartElement();
    keyGame.key = xmlReader.readElementText().toInt();

    return keyGame;
}
