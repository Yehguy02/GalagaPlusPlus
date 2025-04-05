#ifndef PLAYER_H
#define PLAYER_H

#include "health.h"
// #include "powerup.h"

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QTimer>

class Player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)
public:
    explicit Player(QPixmap pixmap);

    void move(qreal xPos);
    void shoot();
    void displayHealth();
    void receiveDamage();
    void receiveHeal();
    void rapidFire();
    void speedBoost();

public slots:
    void setX(qreal x);

signals:
    void playerDied();

protected:

private:
    QPropertyAnimation* animation;
    QList<Health*> health;
    int speed;
};

#endif // PLAYER_H
