#ifndef SCENE_H
#define SCENE_H

#include "player.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QTimer>
#include <QRandomGenerator>

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);
    ~Scene();

    void setPlayer();
    void gameStart();
    void gameStop();

signals:
    void gameEnded();

private:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void spawnEnemy();

    Player* player = nullptr;
    QTimer* timer;
    const qreal LEFTXPOS = -350.0;
};

#endif // SCENE_H
