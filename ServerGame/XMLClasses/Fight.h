#ifndef FIGHT_H
#define FIGHT_H

#include <QString>

class QXmlStreamReader;
class Fight
{
public:
    Fight();
    Fight(QString name1, QString name2, bool isInsert);

    QString toXML();
    static Fight fromXML(QXmlStreamReader &xmlReader);

    QString name1;
    QString name2;
    bool isInsert;
};

#endif // FIGHT_H
