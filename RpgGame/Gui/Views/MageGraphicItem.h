#ifndef MAGEGRAPHICITEM_H
#define MAGEGRAPHICITEM_H

#include "Gui/Views/ActorGraphicsItem.h"

class MageGraphicItem : public ActorGraphicsItem
{
public:
    MageGraphicItem();

    QRectF attack();
};

#endif // MAGEGRAPHICITEM_H
