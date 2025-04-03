#include "bullet.h"

Bullet::Bullet(qreal startX, qreal startY, qreal speed, qreal endY)
    : xPos(startX), yPos(startY), moveSpeed(speed), endPoint(endY)
{

}

Bullet::~Bullet() {
    qDebug() << "Bullet desroyed";
}


