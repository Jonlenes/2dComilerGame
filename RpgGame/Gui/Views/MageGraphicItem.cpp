#include "MageGraphicItem.h"

#include <QPainter>

MageGraphicItem::MageGraphicItem() :
    ActorGraphicsItem()
{
    hp = 50;
    ap = 150;
    hpMax = hp;
    apMax = ap;

    actor = new QPixmap(":/img/sprite/magoo.png");

    width = 40;
    heigth = 50;
    frameActual = 5;
    coutFramesSprites = {3, 1, 3, 1};
    startSprites = {1, 4, 5, 8};
    timeSprite.setInterval(250);

}

QRectF MageGraphicItem::attack()
{
    /*ATAQUE
     * A distancia do ataque será calculada propocionalmente a ap, sendo que a ap
     * 100 consegue atacar a uma distancia correspondente a metade da tela
     */

    qreal x = 0;
    qreal y = 0;
    qreal w = 0;
    qreal h = 0;
    int apBase = 100;

    if (moveDirection == MoveLeft || moveDirection == MoveRigth) {

        w = ((sizeScreen.width() / 2) * (ap / apBase));
        h = heigth;

        if (moveDirection == MoveLeft)
            x -= w;
        else
            x += width;

    } else {

        w = width;
        h = ((sizeScreen.height() / 2) * (ap / apBase));

        if (moveDirection == MoveUp)
            y -= h;
        else
            y += heigth;

    }

    return QRectF(x, y, w, h);
}
