#include "CollisionAlgo.h"

bool CollisionAlgo::detectedCollision(QList<QRectF> listObjects, QRectF rectActor)
{
    for (QRectF rect : listObjects) {
        if (detectedCollision(rect, rectActor))
            return true;
    }

    return false;
}

bool CollisionAlgo::detectedCollision(QRectF rect1, QRectF rect2)
{
    return ((rect1.x() <= rect2.x() + rect2.width()) &&
            (rect1.x() + rect1.width() >= rect2.x() ) &&
            (rect1.y() <= rect2.y() + rect2.height()) &&
            (rect1.y() + rect1.height() >= rect2.y()));
}
