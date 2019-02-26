#ifndef TESTE_H
#define TESTE_H

#include <QGraphicsView>
#include <QRectF>
#include <QProgressBar>

#include "ParserMap/TmxMap.h"
#include "ActorGraphicsItem.h"

enum Actor {
    ActorInternal,
    ActorExternal
};

class GraphicsViewGame : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphicsViewGame(QWidget *parent, int index);

    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *event);

    bool actionPerformed(int key, int actor);

signals:

public slots:
    void slotKeyExternalGame(int key);
    void slotNewPosition(int x, int y);
    void slotSynchronize();

private:
    QList<QPixmap> listPixmap;
    ActorGraphicsItem **actors;
    QProgressBar **progressPlays;

    QList<QRectF> listCollision;
    int index;


    void monthMapOnTheScreen();
    void monthProgressBar();
    void widCompiler();

    QTimer timerSynchronization;
};

#endif // TESTE_H
