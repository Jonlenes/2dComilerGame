#include "NamePlayer.h"

#include <QXmlStreamWriter>
#include <QXmlStreamReader>

NamePlayer::NamePlayer()
{

}

NamePlayer::NamePlayer(QString name) :
    name(name), isInsert(true)
{

}

NamePlayer::NamePlayer(QString name, bool isInsert) :
    name(name), isInsert(isInsert)
{

}

QString NamePlayer::toXML()
{
    QString xml;
    QXmlStreamWriter xmlWriter(&xml);

    xmlWriter.writeStartElement("NamePlayer");
    xmlWriter.writeTextElement("name", name);
    xmlWriter.writeTextElement("isInsert", QString::number(isInsert));
    xmlWriter.writeEndElement();

    return xml;
}

NamePlayer NamePlayer::fromXML(QXmlStreamReader &xmlReader)
{
    NamePlayer namePlayer;

    xmlReader.readNextStartElement();
    namePlayer.name = xmlReader.readElementText();
    xmlReader.readNextStartElement();
    namePlayer.isInsert = xmlReader.readElementText().toInt();

    return namePlayer;
}
