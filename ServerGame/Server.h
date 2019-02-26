#ifndef SERVER_H
#define SERVER_H

#include "XMLClasses/Players.h"

#include <QTcpServer>
#include <QSignalMapper>
#include <QXmlStreamReader>

#include <vector>

using namespace std;

class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server(QHostAddress, qint16);

    void sendBroadcast(QString xml, QTcpSocket *clientSocketExcluded = __null);
    void sendMessegeClint(QTcpSocket *clientSocket, QString xml);

private slots:
    void slotNewConnection();
    void slotClientReadyRead(QObject *socket);
    void slotClientDisconnected(QObject *socket);

signals:
    void newUser(QString hostName, int port, QString nome);

private:
    vector<QTcpSocket *> listClients;
    QSignalMapper *signalMapperRead;
    QSignalMapper *singalMapperDesconnect;

    Players players;

    int indexOf(QTcpSocket *socket);
    void removeClient(QTcpSocket *clientSocket);

};

#endif // SERVER_H
