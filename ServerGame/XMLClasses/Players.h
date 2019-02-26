#ifndef PLAYERS_H
#define PLAYERS_H

#include "NamePlayer.h"
#include "RequestNewGame.h"
#include "Fight.h"

#include <QString>

#include <vector>
#include <iostream>

using namespace std;



class QXmlStreamReader;
class Players
{
public:
    Players();
    ~Players();

    bool addPlayer(NamePlayer namePlayer, int index = -1);
    void removePlayer(int index);
    void addFight(Fight fight);

    int indexOf(QString name);
    QString getName(int index);

    QString toXML();
    static Players fromXML(QXmlStreamReader &xmlReader);

    struct Player {
        Player(QString name, bool isPlaying) :
            name(name), isPlaying(isPlaying) {}

        bool operator == (const Player player) { return name == player.name; }

        QString name;
        bool isPlaying;
    };

    vector< pair<int, int> > listFightsActive;
    vector< Player > listUsers;

};

#endif // PLAYERS_H
