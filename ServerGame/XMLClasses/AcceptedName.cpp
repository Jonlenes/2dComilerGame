#include "AcceptedName.h"

#include <QXmlStreamWriter>

AcceptedName::AcceptedName()
{
}

QString AcceptedName::toXML()
{
    QString xml;
    QXmlStreamWriter xmlWriter(&xml);

    xmlWriter.writeStartElement("AcceptedName");
    xmlWriter.writeEndElement();

    return xml;
}
