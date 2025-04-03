#ifndef PLAYERBULLET_H
#define PLAYERBULLET_H

#include "bullet.h"

#include <QObject>
#include <QSize>
#include <QPropertyAnimation>
#include <QGraphicsScene>

#include <QDebug>

class PlayerBullet : public Bullet
{
    Q_OBJECT
    Q_PROPERTY(qreal y READ y WRITE setY);
public:
    explicit PlayerBullet(qreal startX, qreal startY, qreal speed);
    ~PlayerBullet();
    void move() override;
signals:
private:
};

#endif // PLAYERBULLET_H
