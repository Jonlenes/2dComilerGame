#include "Server.h"
#include "MappingObject.h"
#include "XMLClasses/AlertForUser.h"
#include "XMLClasses/AcceptedName.h"
#include "XMLClasses/KeyGame.h"
#include "XMLClasses/Position.h"

#include <QTcpSocket>
#include <QXmlStreamReader>

#include <iostream>
#include <algorithm>

using namespace std;

Server::Server(QHostAddress , qint16 ) :
    QTcpServer()
{
    signalMapperRead = new QSignalMapper();
    singalMapperDesconnect = new QSignalMapper();

    connect(signalMapperRead, SIGNAL(mapped(QObject*)), this, SLOT(slotClientReadyRead(QObject*)));
    connect(singalMapperDesconnect, SIGNAL(mapped(QObject*)), this, SLOT(slotClientDisconnected(QObject*)));

    connect(this, SIGNAL(newConnection()), SLOT(slotNewConnection()));

    listen(QHostAddress::Any, 10);
}

void Server::slotNewConnection()
{
    if (hasPendingConnections()) {

        QTcpSocket *newClient = nextPendingConnection();

        connect(newClient, SIGNAL(readyRead()), signalMapperRead, SLOT(map()));
        connect(newClient, SIGNAL(disconnected()), singalMapperDesconnect, SLOT(map()));

        signalMapperRead->setMapping(newClient, newClient);
        singalMapperDesconnect->setMapping(newClient, newClient);

        listClients.push_back(newClient);
        players.addPlayer(QString(""));
        sendMessegeClint(newClient, players.toXML());

        emit newUser(newClient->peerAddress().toString(), newClient->peerPort(), "");
    }
}

void Server::slotClientReadyRead(QObject *socket)
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket *> (socket);
    QXmlStreamReader xmlReader(QString(clientSocket->read(1024000)));

    switch (MappingObject::getClass(xmlReader)) {

    case NamePlayerClass:
    {
        NamePlayer namePlayer = NamePlayer::fromXML(xmlReader);
        if (players.addPlayer(namePlayer, indexOf(clientSocket))) {
            sendBroadcast(namePlayer.toXML(), clientSocket);
            sendMessegeClint(clientSocket, AcceptedName().toXML());
            emit newUser(clientSocket->peerAddress().toString(), clientSocket->peerPort(), namePlayer.name);
        } else {
            sendMessegeClint(clientSocket, AlertForUser("Nome de usuário já utilizado.").toXML());
        }

        break;
    }
    case RequestNewGameClass:
    {
        RequestNewGame requestNewGame = RequestNewGame::fromXML(xmlReader);

        if (requestNewGame.state == RequestNewGame::Analisar) {
            sendMessegeClint(listClients[players.indexOf(requestNewGame.nameGuest)], requestNewGame.toXML());
        } else {
            sendMessegeClint(listClients[players.indexOf(requestNewGame.nameWhoRequest)], requestNewGame.toXML());

//            if (requestNewGame.state == RequestNewGame::Accept) {

//                players.listUsers[players.indexOf(requestNewGame.nameGuest)].isPlaying = true;
//                players.listUsers[players.indexOf(requestNewGame.nameWhoRequest)].isPlaying = true;

//                Fight fight(requestNewGame.nameWhoRequest, requestNewGame.nameGuest, true);
//                players.addFight(fight);
//                sendBroadcast(fight.toXML());
//            }
        }

        break;
    }
    case KeyGameClass:
    {
        KeyGame keyGame = KeyGame::fromXML(xmlReader);
        sendMessegeClint(listClients[players.indexOf(keyGame.name)], keyGame.toXML());
        break;
    }

    case PositionClass:
    {
        Position position = Position::fromXML(xmlReader);
        sendMessegeClint(listClients[players.indexOf(position.name)], position.toXML());
        break;
    }

    default:
        break;
    }
}

void Server::slotClientDisconnected(QObject *socket)
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket *> (socket);
    int index = indexOf(clientSocket);
    NamePlayer namePlayer(players.getName(index), false);

    players.removePlayer(index);
    removeClient(clientSocket);

    sendBroadcast(namePlayer.toXML());
}

void Server::sendBroadcast(QString xml, QTcpSocket *clientSocketExcluded)
{
    QByteArray byteArray = xml.toUtf8();

    for (auto i : listClients) {
        if (!clientSocketExcluded || clientSocketExcluded != i)
            i->write(byteArray);
    }
}

void Server::sendMessegeClint(QTcpSocket *clientSocket, QString xml)
{
    clientSocket->write(xml.toUtf8());
}

int Server::indexOf(QTcpSocket *socket)
{
    int size = listClients.size();
    for (int i = 0; i < size; ++i)
        if (listClients[i] == socket)
            return i;

    return -1;
}

void Server::removeClient(QTcpSocket *clientSocket)
{
    listClients.erase(std::remove(listClients.begin(), listClients.end(), clientSocket), listClients.end());
}
