#include "MappingObject.h"

#include <QXmlStreamReader>
#include <QStringList>

const QStringList MappingObject::listNameClass = QStringList({"Players", "NamePlayer",
                                                              "RequestNewGame", "AcceptedName",
                                                              "AlertForUser", "Fight",
                                                              "KeyGame", "Pos"});


int MappingObject::getClass(QXmlStreamReader &xmlReader)
{
    xmlReader.readNextStartElement();
    return listNameClass.indexOf(xmlReader.name().toString());
}
