#include "playerbullet.h"
#include "enemy.h"
#include "enemybullet.h"

PlayerBullet::PlayerBullet(qreal startX, qreal startY, qreal speed)
    : Bullet(startX, startY, speed, -500) // xPos, yPos, moveSpeed, endPoint
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
    // qDebug() << "Player bullet destroyed";
}

void playerBulletHit() {
    // qDebug() << "Plyrbllt hit shit!!";
}

void PlayerBullet::setY(qreal y) {
    setPos(x(), y);

    if (collide()) {
        emit playerBulletHit();
        deleteLater();
    }
}

void PlayerBullet::move() {
    animation = new QPropertyAnimation(this, "y");
    animation->setDuration(moveSpeed);
    animation->setStartValue(yPos);
    animation->setEndValue(-500.0);

    connect(animation, &QPropertyAnimation::finished, [=]() {
        scene()->removeItem(this);
        delete(this);
    });

    animation->start();
}

bool PlayerBullet::collide() {
    QList<QGraphicsItem*> collideItems = collidingItems();
    for (QGraphicsItem* item : collideItems) {
        Enemy* p = dynamic_cast<Enemy*>(item);
        EnemyBullet* e = dynamic_cast<EnemyBullet*>(item);
        if (p || e) {
            delete(item);
            return true;
        }
    }
    return false;
}
