#ifndef POWERUP_H
#define POWERUP_H

#include "player.h"

#include <QObject>
#include <QRandomGenerator>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QGraphicsScene>

class PowerUp : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal y READ y WRITE setY)
public:
    explicit PowerUp(Player* player = nullptr);
    ~PowerUp();

    void buffEffect();
    void move();

public slots:
    void setY(qreal y);

signals:

private:
    bool collide();

    enum class PowerTypes{
        Repair,
        RapidFire,
        SpeedBoost,
    };
    PowerTypes power;
    QPixmap pixmap;
    QPropertyAnimation* animation;
    Player* player;
};

#endif // POWERUP_H
