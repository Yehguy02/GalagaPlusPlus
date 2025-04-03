#include "scene.h"
#include "playerbullet.h"

#include <cmath>

Scene::Scene(QObject *parent)
    : QGraphicsScene(parent)
{

}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    // get mouse x position
    qreal mouseX = event->scenePos().x();

    // set player pos to mouseX position
    movePlayer(mouseX);

    // default handling
    QGraphicsScene::mousePressEvent(event);
}

void Scene::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Space) {
        playerShoot();
    }
}

void Scene::setPlayer(Player* p) {
    player = p;
}

void Scene::movePlayer(qreal xPos) {
    if (!player) return;

    // set moving speed depends on distant
    qreal distance = abs(xPos - player->pos().x());
    qreal baseSpeed = 3;

    int duration = static_cast<int>(distance * baseSpeed);

    // duration = std::max(100, std::min(duration, 1000)); // clamp between 100ms to 1000ms

    // make animation object to animate player moving
    QPropertyAnimation* animation = new QPropertyAnimation(player, "position");
    animation->setDuration(duration); // in ms
    animation->setStartValue(player->pos());
    animation->setEndValue(QPointF(xPos, player->y()));
    animation->start();
}

void Scene::playerShoot() {
    if (!player) return;

    Bullet* bullet = new PlayerBullet(player->pos().x(), player->pos().y(), 1000.0);
    addItem(bullet);
    bullet->move();
}



