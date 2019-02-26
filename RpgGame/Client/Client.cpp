#include "Client.h"
#include "../ServerGame/MappingObject.h"
#include "../ServerGame/XMLClasses/Players.h"
#include "../ServerGame/XMLClasses/AlertForUser.h"
#include "../ServerGame/XMLClasses/RequestNewGame.h"
#include "../ServerGame/XMLClasses/Fight.h"
#include "../ServerGame/XMLClasses/KeyGame.h"
#include "../ServerGame/XMLClasses/Position.h"

#include <QXmlStreamReader>

#include <iostream>
using namespace std;

Cliente *Cliente::cliente = 0;

Cliente::Cliente() :
    QTcpSocket()
{
    connect(this, SIGNAL(readyRead()), SLOT(slotReadyRead()));
}

Cliente::~Cliente()
{
    if (cliente) delete cliente;
}

Cliente *Cliente::getInstanse()
{
    if (!cliente) cliente = new Cliente();
    return cliente;
}

void Cliente::setName(QString name)
{
    this->name = name;
}

void Cliente::makeRequestNewGame(QString name)
{
    sendMessege(RequestNewGame(this->name, name).toXML());
}

void Cliente::responseNewGamePending(bool result)
{
    RequestNewGame requestNewGame = listRequestGame[0];

    listRequestGame.erase(std::remove(listRequestGame.begin(), listRequestGame.end(), requestNewGame),
                          listRequestGame.end());

    requestNewGame.state = result;
    sendMessege(requestNewGame.toXML());

    if (result)
        nameOpponent = requestNewGame.nameWhoRequest;

    if (!result && !listRequestGame.empty())
        emit signalPlayRequest(listRequestGame[0].nameWhoRequest);
}

void Cliente::connectToHost(QString hostName, qint16 port, int time = 5000)
{
    QTcpSocket::connectToHost(QHostAddress(hostName), port);

    if (!waitForConnected(time)) {
        throw QString("Falha na comunicação com o servidor.");
    }
}

bool Cliente::sendMessege(QString xml)
{
    return write(xml.toUtf8()) == xml.length();
}

void Cliente::sendKeyGame(int key)
{
    sendMessege(KeyGame(nameOpponent, key).toXML());
}

void Cliente::sendPosition(int x, int y)
{
    sendMessege(Position(x, y, nameOpponent).toXML());
}

void Cliente::slotReadyRead()
{
    QXmlStreamReader xmlReader(QString(read(1024000)));

    switch (MappingObject::getClass(xmlReader)) {

    case PlayersClass:
    {
        emit signalSetUserList(Players::fromXML(xmlReader));
        break;
    }

    case NamePlayerClass:
    {
        NamePlayer namePlayer = NamePlayer::fromXML(xmlReader);

        if (namePlayer.isInsert) {
            emit signalNewUser(namePlayer.name);
        } else {
            emit signalUserDisconnected(namePlayer.name);
        }

        break;
    }

    case AcceptedNameClass:
    {
        emit signalAcceptedName();
        break;
    }

    case AlertForUserClass:
    {
        emit signalAlertForUser(AlertForUser::fromXML(xmlReader).message);
        break;
    }

    case RequestNewGameClass:
    {
        RequestNewGame requestNewGame = RequestNewGame::fromXML(xmlReader);
        switch (requestNewGame.state) {

        case RequestNewGame::Analisar:
            listRequestGame.push_back(requestNewGame);
            if (listRequestGame.size() == 1)
                emit signalPlayRequest(requestNewGame.nameWhoRequest);
            break;

        case RequestNewGame::Accept:
            nameOpponent = requestNewGame.nameGuest;
            emit signalGameAccept(1);
            break;

        case RequestNewGame::Rejeited:
            emit signalAlertForUser(requestNewGame.nameGuest + " não aceitou jogar com você.");
            break;
        default:
            break;
        }

        break;
    }

    case FightClass:
    {
        Fight figth = Fight::fromXML(xmlReader);

        if (figth.isInsert)
            emit signalNewFightStarted(figth.name1, figth.name2);
        else
            emit signalFightFinalized(figth.name1, figth.name2);

        break;
    }

    case KeyGameClass:
    {
        signalKeyGame(KeyGame::fromXML(xmlReader).key);
        break;
    }

    case PositionClass:
    {
        Position position = Position::fromXML(xmlReader);
        signalNewPosition(position.x, position.y);
        break;
    }

    default:
        break;
    }
}
