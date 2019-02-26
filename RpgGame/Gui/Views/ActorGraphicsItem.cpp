#include "ActorGraphicsItem.h"
#include "CollisionAlgo.h"

#include <QPainter>
#include <QGraphicsScene>
#include <QApplication>
#include <QDesktopWidget>

#include <QDebug>

ActorGraphicsItem::ActorGraphicsItem() :
    QGraphicsObject(), hp(0), ap(0), hpMax(0), apMax(0)
{
    setFlag(ItemIsMovable);
    actor = new QPixmap(":/img/actor.png");

    width = 80;
    heigth = 105;
    frameActual = 13;
    coutFramesSprites = {4, 4, 4, 4};
    startSprites = {5, 13, 9, 1};
    timeSprite.setInterval(250);
    isShowAnimation = false;
    sizeScreen = QApplication::desktop()->size();
    moveDirection = MoveUp;

    connect(&timeSprite, SIGNAL(timeout()), this, SLOT(nextFrame()));


    test = 0;

}

QRectF ActorGraphicsItem::boundingRect() const
{

    return QRectF(0, 0, width, heigth);
}

void ActorGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(0, 0, width, heigth, getImgage(frameActual - 1));

    painter->setPen(QPen(Qt::red, 3));
    painter->drawRect(attack());
}

void ActorGraphicsItem::move(int moveDirection, QList<QRectF> listObjects)
{

    test++;

    this->moveDirection = moveDirection;
    double x = 0;
    double y = 0;

    switch (moveDirection) {
    case MoveUp:
        y = -3.5;
        break;
    case MoveDown:
        y = 3.5;
        break;
    case MoveRigth:
        x = 3.5;
        break;
    case MoveLeft:
        x = -3.5;
        break;
    }


    if (CollisionAlgo::detectedCollision(listObjects, QRectF(pos().x() + x, pos().y() + y, width, heigth)))
        return;

    if (!isShowAnimation) {
        frameActual = startSprites[moveDirection];
        timeSprite.start();
        isShowAnimation = true;
    }
    setPos(pos().x() + x, pos().y() + y);
}

void ActorGraphicsItem::stopSprite()
{
    timeSprite.stop();
    isShowAnimation = false;
    frameActual = startSprites[moveDirection];
}

QRectF ActorGraphicsItem::attack()
{
    /*ATAQUE
         * A distancia do ataque será calculada propocionalmente a ap, sendo que a ap
         * 100 consegue atacar a uma distancia correspondente a metade da tela
         */

    qreal x = 0;
    qreal y = 0;
    qreal w = 0;
    qreal h = 0;
    int lengthAtaque = 100;

    if (moveDirection == MoveLeft || moveDirection == MoveRigth) {

        w = lengthAtaque;
        h = heigth;

        if (moveDirection == MoveLeft)
            x -= w;
        else
            x += width;

    } else {

        w = width;
        h = lengthAtaque;

        if (moveDirection == MoveUp)
            y -= h;
        else
            y += heigth;

    }

    isAttacking = true;

    return QRectF(x, y, w, h);
}

void ActorGraphicsItem::tomarPorcao(int tipoPorcao)
{
    if (tipoPorcao == 1) {
        hp *= 1.2;
        if (hp > hpMax) hp = hpMax;
    } else {
        ap *= 1.1;
    }
}

void ActorGraphicsItem::serAtingido(int force)
{
    hp -= force * 0.1;

    if (hp <= 0) {
        hp = 0;
        //Emitir morto;
    }

    emit signalLifeChange(hp);
}

QPixmap ActorGraphicsItem::getImgage(int i)
{
    return actor->copy((i % (actor->width() / width)) * width, (i / (actor->width() / width)) * heigth, width, heigth);
}

void ActorGraphicsItem::nextFrame()
{
    if (frameActual + 1 < startSprites[moveDirection] + coutFramesSprites[moveDirection])
        frameActual++;
    else
        frameActual = startSprites[moveDirection];

    update();
    timeSprite.start();
}
