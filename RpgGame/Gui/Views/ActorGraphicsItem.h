#ifndef GRAPHICWIDGETITEM_H
#define GRAPHICWIDGETITEM_H

#include <QGraphicsItem>
#include <QTimer>

#include <vector>

class QAbstractAnimation;

enum MoveDirection {
    MoveLeft,
    MoveUp,
    MoveRigth,
    MoveDown
};

class ActorGraphicsItem : public QGraphicsObject
{
    Q_OBJECT

public:
    explicit ActorGraphicsItem();

    QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    virtual void move(int moveDirection, QList<QRectF> listObjects);
    virtual void stopSprite();
    virtual QRectF attack();
    virtual void tomarPorcao(int tipoPorcao);
    virtual void serAtingido(int force);

signals:
    void signalLifeChange(int);

private slots:
    void nextFrame();

public:
    QPixmap *actor;

    QTimer timeSprite;
    int moveDirection;
    std::vector<int> startSprites;
    std::vector<int> coutFramesSprites;
    int width;
    int heigth;
    int frameActual;
    bool isShowAnimation;
    bool isAttacking;

    QSize sizeScreen;

    int hp;
    int ap;
    int hpMax;
    int apMax;

    QPixmap getImgage(int i);

    int test;
};

#endif // GRAPHICWIDGETITEM_H
