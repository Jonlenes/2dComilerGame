#ifndef NAMEPLAYER_H
#define NAMEPLAYER_H

#include <QString>

class QXmlStreamReader;
class NamePlayer
{
public:
    NamePlayer();
    NamePlayer(QString name);
    NamePlayer(QString name, bool isInsert);

    QString toXML();
    static NamePlayer fromXML(QXmlStreamReader &xmlReader);

    QString name;
    bool isInsert;
};

#endif // NAMEPLAYER_H
