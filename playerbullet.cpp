#include "playerbullet.h"

PlayerBullet::PlayerBullet(qreal startX, qreal startY, qreal speed)
    : Bullet(startX, startY, speed, -500)
{
    // assign graphics to player's bullet
    QSize bulletSize(10, 10);
    QPixmap pixmap(QPixmap(":/images/player bullet.png"));
    QPixmap scaledPixmap = pixmap.scaled(bulletSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

    // set graphics : -scaledPixmap.width() / 2, 0
    setOffset(-scaledPixmap.width() / 2, -scaledPixmap.height());
    setPixmap(scaledPixmap);

    // set position of the bullet
    setPos(xPos, yPos);
}

PlayerBullet::~PlayerBullet() {

}

void PlayerBullet::move() {
    QPropertyAnimation* animation = new QPropertyAnimation(this, "y");
    animation->setDuration(moveSpeed);
    animation->setStartValue(yPos);
    animation->setEndValue(-500.0);

    connect(animation, &QPropertyAnimation::finished, [=]() {
        scene()->removeItem(this);
        delete(this);
    });

    animation->start();
}
