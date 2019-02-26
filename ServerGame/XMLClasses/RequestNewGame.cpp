#include "RequestNewGame.h"

#include <QXmlStreamWriter>
#include <QXmlStreamReader>

RequestNewGame::RequestNewGame()
{
    state = Analisar;
}

RequestNewGame::RequestNewGame(QString nameWhoRequest, QString nameGuest) :
    nameWhoRequest(nameWhoRequest), nameGuest(nameGuest)
{
    state = Analisar;
}

QString RequestNewGame::toXML()
{
    QString xml;
    QXmlStreamWriter xmlWriter(&xml);

    xmlWriter.writeStartElement("RequestNewGame");
    xmlWriter.writeTextElement("nameWhoRequest", nameWhoRequest);
    xmlWriter.writeTextElement("nameGuest", nameGuest);
    xmlWriter.writeTextElement("state", QString::number(state));
    xmlWriter.writeEndElement();

    return xml;
}

RequestNewGame RequestNewGame::fromXML(QXmlStreamReader &xmlReader)
{
    RequestNewGame requestNewGame;

    xmlReader.readNextStartElement();
    requestNewGame.nameWhoRequest = xmlReader.readElementText();

    xmlReader.readNextStartElement();
    requestNewGame.nameGuest = xmlReader.readElementText();

    xmlReader.readNextStartElement();
    requestNewGame.state = xmlReader.readElementText().toInt();

    return requestNewGame;
}

bool RequestNewGame::operator ==(const RequestNewGame &requestNewGame)
{
    return (nameWhoRequest == requestNewGame.nameWhoRequest);
}
