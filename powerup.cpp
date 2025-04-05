#include "powerup.h"

PowerUp::PowerUp(Player* player)
    : player(player)
{
    // random buff type
    int randomInt = QRandomGenerator::global()->bounded(0, 3);
    switch (randomInt) {
    case 0: // repair
        pixmap = QPixmap(":/images/Repair Kit.png");
        power = PowerTypes::Repair;
        break;
    case 1: // rapid fire
        pixmap = QPixmap(":/images/Rapid Fire.png");
        power = PowerTypes::RapidFire;
        break;
    case 2: // speed boost
        pixmap = QPixmap(":/images/Velocity Boost.png");
        power = PowerTypes::SpeedBoost;
        break;
    default:
        pixmap = QPixmap(":/images/Repair Kit.png");
        power = PowerTypes::Repair;
        qDebug() << "> Power up random error: out of PowerTypes range";
    }

    QSize buffSize(50, 50);
    QPixmap scaledPixmap = pixmap.scaled(buffSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    setPixmap(scaledPixmap);
}

PowerUp::~PowerUp() {

}

void PowerUp::setY(qreal y) {
    setPos(x(), y);

    if (collide()) {
        buffEffect();
        delete(this);
    }
}

void PowerUp::buffEffect() {
    // make effect depends on power type
    switch (power) {
    case PowerTypes::Repair:
        player->receiveHeal();
        break;
    case PowerTypes::RapidFire:
        player->rapidFire();
        break;
    case PowerTypes::SpeedBoost:
        player->speedBoost();
        break;
    }
}

void PowerUp::move() {
    // do the animation
    animation = new QPropertyAnimation(this, "y");
    animation->setDuration(8000); // in ms
    animation->setStartValue(-600.0);
    animation->setEndValue(500.0);

    connect(animation, &QPropertyAnimation::finished, [=]() {
        scene()->removeItem(this);
        delete(this);
    });

    animation->start();
}

bool PowerUp::collide() {
    QList<QGraphicsItem*> collideItems = collidingItems();
    for (QGraphicsItem* item : collideItems) {
        Player* p = dynamic_cast<Player*>(item);
        if (p) return true;
    }
    return false;
}
