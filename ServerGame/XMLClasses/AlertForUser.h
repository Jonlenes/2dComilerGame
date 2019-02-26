#ifndef AlertForUser_H
#define AlertForUser_H

#include <QString>

class QXmlStreamReader;
class AlertForUser
{
public:
    AlertForUser(QString message);

    QString toXML();
    static AlertForUser fromXML(QXmlStreamReader &xmlReader);

    QString message;
};

#endif // AlertForUser_H
