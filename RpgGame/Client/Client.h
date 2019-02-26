#ifndef CLIENTE_H
#define CLIENTE_H

#include "../ServerGame/XMLClasses/Players.h"
#include "../ServerGame/XMLClasses/RequestNewGame.h"

#include <QTcpSocket>
#include <QHostAddress>

#include <vector>

class Cliente : public QTcpSocket
{
    Q_OBJECT

public:
    Cliente();
    ~Cliente();

    static Cliente *getInstanse();
    void setName(QString name);
    void makeRequestNewGame(QString name);
    void responseNewGamePending(bool result);

    void connectToHost(QString hostName, qint16 port, int time);
    bool sendMessege(QString xml);
    void sendKeyGame(int key);
    void sendPosition(int x, int y);

private slots:
    void slotReadyRead();

signals:
    void signalSetUserList(Players players);
    void signalNewUser(QString name);
    void signalUserDisconnected(QString name);
    void signalAcceptedName();
    void signalAlertForUser(QString text);
    void signalPlayRequest(QString name);
    void signalNewFightStarted(QString name1, QString name2);
    void signalFightFinalized(QString name1, QString name2);
    void signalGameAccept(int index);
    void signalKeyGame(int key);
    void signalNewPosition(int x, int y);

private:
    QHostAddress addressServer;
    quint16 portServer;

    QString name;
    QString nameOpponent;
    vector<RequestNewGame> listRequestGame;

    static Cliente *cliente;
};

#endif // CLIENTE_H
