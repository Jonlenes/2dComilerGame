#include "NinjaGraphicItem.h"

NinjaGraphicItem::NinjaGraphicItem() :
    ActorGraphicsItem()
{
    hp = 100;
    ap = 100;
    hpMax = hp;
    apMax = ap;

    actor = new QPixmap(":/img/sprite/ninja.png");

    width = 30;
    heigth = 34;
    frameActual = 8;
    coutFramesSprites = {3, 3, 3, 3};
    startSprites = {4, 10, 1, 7};
    timeSprite.setInterval(250);
}
