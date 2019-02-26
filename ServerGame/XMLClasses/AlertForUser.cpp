#include "AlertForUser.h"

#include <QXmlStreamWriter>


AlertForUser::AlertForUser(QString message) :
    message(message)
{

}

QString AlertForUser::toXML()
{
    QString xml;
    QXmlStreamWriter xmlWriter(&xml);

    xmlWriter.writeStartElement("AlertForUser");
    xmlWriter.writeTextElement("message", message);
    xmlWriter.writeEndElement();

    return xml;
}

AlertForUser AlertForUser::fromXML(QXmlStreamReader &xmlReader)
{
    xmlReader.readNextStartElement();
    return AlertForUser(xmlReader.readElementText());
}
