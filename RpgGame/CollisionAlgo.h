#ifndef COLLISIONALGO_H
#define COLLISIONALGO_H

#include <QList>
#include <QRectF>

class CollisionAlgo
{
public:

    static bool detectedCollision(QList<QRectF> listObjects, QRectF rectActor);
    static bool detectedCollision(QRectF rect1, QRectF rect2);
};

#endif // COLLISIONALGO_H
