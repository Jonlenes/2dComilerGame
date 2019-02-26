#ifndef KEYGAME_H
#define KEYGAME_H

#include <QString>

class QXmlStreamReader;
class KeyGame
{
public:
    KeyGame();
    KeyGame(QString name, int key);

    QString toXML();
    static KeyGame fromXML(QXmlStreamReader &xmlReader);

    QString name;
    int key;
};

#endif // KEYGAME_H
