#ifndef MONTHOBJECT_H
#define MONTHOBJECT_H

#include <QString>

enum NameClasse {
    PlayersClass,
    NamePlayerClass,
    RequestNewGameClass,
    AcceptedNameClass,
    AlertForUserClass,
    FightClass,
    KeyGameClass,
    PositionClass
};

class QXmlStreamReader;
class MappingObject
{
public:

    static int getClass(QXmlStreamReader &xmlReader);

private:
    static const QStringList listNameClass;
};


#endif // MONTHOBJECT_H
