#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

#include "bullet.h"

#include <QPropertyanimation>
#include <QGraphicsScene>

class EnemyBullet : public Bullet
{
    Q_OBJECT
    Q_PROPERTY(qreal y READ y WRITE setY)
public:
    explicit EnemyBullet(qreal startX, qreal startY);
    ~EnemyBullet();
    void move() override;

signals:
    void enemyBulletHit();

public slots:
    void setY(qreal y);

private:
    bool collide() override;

    QPropertyAnimation* animation;
};

#endif // ENEMYBULLET_H
