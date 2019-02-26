#include "GraphicsViewGame.h":>NGGKvc
#include "MageGraphicItem.h"
#include "KnightGraphicItem.h"
#include "CollisionAlgo.h"
#include "Client/Client.h"

#include <QPainter>
#include <QFile>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QDebug>
#include <QScrollBar>

#include <iostream>


GraphicsViewGame::GraphicsViewGame(QWidget *parent, int index) :
    QGraphicsView(parent), index(index)
{
    QGraphicsScene* viewScene = new QGraphicsScene(0, 0, 1366, 768);
    setScene(viewScene);

    monthMapOnTheScreen();
    monthProgressBar();

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    timerSynchronization.setInterval(100);

    connect(Cliente::getInstanse(), SIGNAL(signalKeyGame(int)), this, SLOT(slotKeyExternalGame(int)));
    connect(Cliente::getInstanse(), SIGNAL(signalNewPosition(int,int)), this, SLOT(slotNewPosition(int,int)));
    connect(&timerSynchronization, SIGNAL(timeout()), this, SLOT(slotSynchronize()));

    timerSynchronization.start();
}


void GraphicsViewGame::monthMapOnTheScreen()
{
    QFile file(":/img/conclusao.tmx");
    TmxMap *tmxMap;

    file.open(QFile::ReadOnly);
    tmxMap = TmxMap::loadTmxMap( (char *) QString(file.readAll()).toStdString().c_str() );

    for (auto i : tmxMap->tilesets) {
        QString fileName = QString::fromStdString(i->filename);
        listPixmap.push_back(QPixmap(":/img/" + fileName.right(fileName.length() - fileName.lastIndexOf("/") - 1)));
    }

    
    for (auto layer : tmxMap->layers) {

        for (int i = 0; i < tmxMap->height; i++) {
            for (int j = 0; j < tmxMap->width; ++j) {

                int grid = layer->data[i * tmxMap->width + j];

                if (grid == 0) continue;

                TmxMapTileset *tileset = nullptr;
                unsigned int k = 0;

                for (; k < tmxMap->tilesets.size(); ++k) {
                    if (grid >= tmxMap->tilesets[k]->firstGid &&
                            (k + 1 == tmxMap->tilesets.size() || grid < tmxMap->tilesets[k + 1]->firstGid)) {
                        tileset = tmxMap->tilesets[k];
                        break;
                    }
                }

                int xImageResult = j * tmxMap->tileWidth;
                int yImageResult = i * tmxMap->tileHeight;

                grid -= tileset->firstGid;

                int xImageOriginal = (grid % (listPixmap[k].width() / tileset->tileWidth)) * tileset->tileWidth;
                int yImageOriginal = (grid / (listPixmap[k].width() / tileset->tileWidth)) * tileset->tileHeight;

                QGraphicsPixmapItem * item = scene()->addPixmap(listPixmap[k].copy(xImageOriginal, yImageOriginal, tileset->tileWidth, tileset->tileHeight));
                item->setPos(xImageResult, yImageResult);
            }
        }
    }



    actors = new ActorGraphicsItem*[2];

    actors[0] = new KnightGraphicItem();
    actors[1] = new MageGraphicItem();

    scene()->addItem(actors[0]);
    scene()->addItem(actors[1]);

    for (auto object : tmxMap->groups[0]->objects) {
        //listCollision.push_back(QRectF(object->x, object->y, object->width, object->height));
        //scene()->addRect(QRectF(object->x, object->y, object->width, object->height));
    }

}

void GraphicsViewGame::monthProgressBar()
{
    int width = 150;
    int height = 20;

    progressPlays = new QProgressBar*[2];
    progressPlays[0] = new QProgressBar(this);
    progressPlays[1] = new QProgressBar(this);

    progressPlays[0]->setRange(0, actors[0]->hpMax);
    progressPlays[0]->setValue(actors[0]->hp);
    progressPlays[0]->setGeometry(10, 10, width, height);

    progressPlays[1]->setRange(0, actors[1]->hpMax);
    progressPlays[1]->setValue(actors[1]->hp);
    progressPlays[1]->setGeometry(scene()->width() - width + 10, 10, width, height);

    connect(actors[0], SIGNAL(signalLifeChange(int)), progressPlays[0], SLOT(setValue(int)));
    connect(actors[1], SIGNAL(signalLifeChange(int)), progressPlays[1], SLOT(setValue(int)));
}

void GraphicsViewGame::keyPressEvent(QKeyEvent *e)
{
    actionPerformed(e->key(), ActorInternal);
    Cliente::getInstanse()->sendKeyGame(e->key());
}


void GraphicsViewGame::keyReleaseEvent(QKeyEvent *event)
{
    if (!event->isAutoRepeat()) {
        actors[ActorInternal]->stopSprite();
    }
}

bool GraphicsViewGame::actionPerformed(int key, int actor)
{
    qDebug() << QString::number(actors[(actor + index) % 2]->test);
    if (key >= Qt::Key_Left && key <= Qt::Key_Down) {

        actors[(actor + index) % 2]->move(key - Qt::Key_Left, listCollision);
        scene()->update();

        return true;

    } else {
        switch (key) {
        case Qt::Key_A:
        {
            QRectF rectAttack = actors[(actor + index) % 2]->attack();
            if (CollisionAlgo::detectedCollision(rectAttack, actors[1 - ((actor + index) % 2)]->boundingRect())) {
                actors[1 - ((actor + index) % 2)]->serAtingido(actors[(actor + index) % 2]->ap);
            }

            scene()->update();
            return true;

            break;
        }

        case Qt::Key_D:
            break;

        case Qt::Key_P:
            break;
        }
    }

    return false;
}

void GraphicsViewGame::slotKeyExternalGame(int key)
{
    actionPerformed(key, ActorExternal);
}

void GraphicsViewGame::slotNewPosition(int x, int y)
{
    if (actors[1 - index]->pos().x() != x ||
            actors[1 - index]->pos().y() != y)
        actors[1 - index]->setPos(x, y);
}

void GraphicsViewGame::slotSynchronize()
{
    Cliente::getInstanse()->sendPosition(actors[index]->pos().x(),
            actors[index]->pos().y());

    timerSynchronization.start();
}
