#include "enemybullet.h"
#include "player.h"

#include <cmath>

EnemyBullet::EnemyBullet(qreal startX, qreal startY)
    : Bullet(startX, startY, 5, 500) // xPos, yPos, moveSpeed, endPoint
{
    // assign graphics to player's bullet
    QSize bulletSize(10, 10);
    QPixmap pixmap(QPixmap(":/images/enemy bullet.png"));
    QPixmap scaledPixmap = pixmap.scaled(bulletSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

    // set graphics : -scaledPixmap.width() / 2, 0
    setOffset(-scaledPixmap.width() / 2, -scaledPixmap.height());
    setPixmap(scaledPixmap);

    // set position of the bullet
    setPos(xPos, yPos);
}

EnemyBullet::~EnemyBullet() {
    // qDebug() << "Enemyyy bullet destroyed";
}

void EnemyBullet::setY(qreal y) {
    setPos(x(), y);

    if (collide()) {
        emit EnemyBullet::enemyBulletHit();
        delete(this);
    }
}

void EnemyBullet::move() {
    // make bullet speed constant
    qreal distance = abs(600 - y());

    int duration = static_cast<int>(distance * moveSpeed);

    animation = new QPropertyAnimation(this, "y");
    animation->setDuration(duration);
    animation->setStartValue(yPos);
    animation->setEndValue(550.0);

    connect(animation, &QPropertyAnimation::finished, [=]() {
        scene()->removeItem(this);
        delete(this);
    });

    animation->start();
}

bool EnemyBullet::collide() {
    QList<QGraphicsItem*> collideItems = collidingItems();
    for (QGraphicsItem* item : collideItems) {
        Player* p = dynamic_cast<Player*>(item);
        if (p) return true;
    }
    return false;
}
