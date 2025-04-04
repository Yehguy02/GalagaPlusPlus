#ifndef ENEMY_H
#define ENEMY_H

#include "scene.h"

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QGraphicsScene>
#include <QTimer>
#include <QRandomGenerator>

class Enemy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal y READ y WRITE setY)
public:
    explicit Enemy(Scene* scene, qreal xPos);
    ~Enemy();

    void move();

public slots:
    void setY(qreal y);

signals:
    void enemyHit();

private:
    void deleteSelf();
    void shootBullet();
    bool collide();

    Scene* scene;
    QPropertyAnimation* animation;
    QPixmap graphics;
    QTimer* timer;
    qreal xPos;
};

#endif // ENEMY_H
