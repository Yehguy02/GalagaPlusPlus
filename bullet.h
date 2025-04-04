#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Bullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Bullet(qreal startX, qreal startY, qreal speed, qreal endY);
    virtual void move() = 0;

public slots:

signals:
    void bulletDestroyed();

protected:
    virtual bool collide() = 0;

    qreal xPos;
    qreal yPos;
    qreal moveSpeed;
    qreal endPoint;
};

#endif // PLAYERBULLET_H
