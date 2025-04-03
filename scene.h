#ifndef SCENE_H
#define SCENE_H

#include "player.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPropertyAnimation>
#include <QGraphicsItem>
#include <QKeyEvent>

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);

    void setPlayer(Player* p);

signals:
private:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void movePlayer(qreal mouseX);
    void playerShoot();

    Player* player = nullptr;
};

#endif // SCENE_H
