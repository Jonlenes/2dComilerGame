#ifndef REQUESTNEWGAME_H
#define REQUESTNEWGAME_H

#include <QString>
class QXmlStreamReader;

class RequestNewGame
{
public:
    RequestNewGame();
    RequestNewGame(QString nameWhoRequest, QString nameGuest);

    QString toXML();
    static RequestNewGame fromXML(QXmlStreamReader &xmlReader);
    bool operator == (const RequestNewGame &requestNewGame);




    QString nameWhoRequest;
    QString nameGuest;
    int state;

    enum State {
        Rejeited,
        Accept,
        Analisar
    };
};

#endif // REQUESTNEWGAME_H
