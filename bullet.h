#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsPixmapItem>

#include <QDebug>

class Bullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Bullet(qreal startX, qreal startY, qreal speed, qreal endY);
    ~Bullet();
public slots:
    virtual void move() = 0;
signals:
    void bulletDestroyed();
protected:
    qreal xPos;
    qreal yPos;
    qreal moveSpeed;
    qreal endPoint;
};

#endif // PLAYERBULLET_H
