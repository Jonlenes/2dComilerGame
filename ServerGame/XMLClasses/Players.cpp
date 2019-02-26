#include "Players.h"

#include <QXmlStreamWriter>
#include <QXmlStreamReader>

#include <algorithm>

Players::Players()
{
}

Players::~Players()
{

}

bool Players::addPlayer(NamePlayer namePlayer, int index)
{
    if (!namePlayer.name.isEmpty()) {
        for (auto i : listUsers) {
            if (i.name == namePlayer.name)
                return false;
        }
    }

    if (index != -1)
        listUsers[index] = Player(namePlayer.name, false);
    else
        listUsers.push_back(Player(namePlayer.name, false));

    return true;
}

void Players::removePlayer(int index)
{
    listUsers.erase(std::remove(listUsers.begin(), listUsers.end(),
                                static_cast<const Player> (listUsers[index])), listUsers.end());
}

void Players::addFight(Fight fight)
{
    listFightsActive.push_back(make_pair(indexOf(fight.name1), indexOf(fight.name2)));
}

int Players::indexOf(QString name)
{
    int size = listUsers.size();
    for (int i = 0; i < size; ++i)
        if (listUsers[i].name == name)
            return i;

    return -1;
}

QString Players::getName(int index)
{
    return listUsers[index].name;
}

QString Players::toXML()
{
    QString xml;
    QXmlStreamWriter xmlWriter(&xml);

    xmlWriter.writeStartElement("Players");

    for (auto i : listFightsActive) {
        xmlWriter.writeTextElement("listFightsActive", QString::number(i.first));
        xmlWriter.writeTextElement("listFightsActive", QString::number(i.second));
    }

    for (auto i : listUsers) {
        if (i.name != "") {
            xmlWriter.writeTextElement("listUsers", i.name);
            xmlWriter.writeTextElement("listUsers", QString::number(i.isPlaying));
        }
    }

    xmlWriter.writeEndElement();

    return xml;
}

Players Players::fromXML(QXmlStreamReader &xmlReader)
{
    Players players;

    while (xmlReader.readNextStartElement(), xmlReader.name() == "listFightsActive") {

        int indexPlay1 = xmlReader.readElementText().toInt();
        xmlReader.readNextStartElement();
        int indexPlay2 = xmlReader.readElementText().toInt();

        players.listFightsActive.push_back(make_pair(indexPlay1, indexPlay2));
    }

    while (xmlReader.name() == "listUsers") {

        QString name = xmlReader.readElementText();
        xmlReader.readNextStartElement();
        bool isPlayed = static_cast<bool> (xmlReader.readElementText().toInt());

        players.listUsers.push_back(Player(name, isPlayed));

        xmlReader.readNextStartElement();
    }

    return players;
}
