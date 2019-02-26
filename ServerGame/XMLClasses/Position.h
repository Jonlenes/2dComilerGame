#ifndef POSITION_H
#define POSITION_H

#include <QString>

class QXmlStreamReader;
class Position
{
public:
    Position();
    Position(int x, int y, QString name);

    QString toXML();
    static Position fromXML(QXmlStreamReader &xmlReader);

    int x;
    int y;
    QString name;
};

#endif // POSITION_H
