#ifndef PLAYERBULLET_H
#define PLAYERBULLET_H

#include "bullet.h"

#include <QObject>
#include <QSize>
#include <QPropertyAnimation>
#include <QGraphicsScene>

class PlayerBullet : public Bullet
{
    Q_OBJECT
    Q_PROPERTY(qreal y READ y WRITE setY);
public:
    explicit PlayerBullet(qreal startX, qreal startY, qreal speed);
    ~PlayerBullet();
    void move() override;

public slots:
    void setY(qreal y);

signals:

private:
    bool collide() override;

    QPropertyAnimation* animation;

};

#endif // PLAYERBULLET_H
