#include "player.h"
#include "playerbullet.h"

Player::Player(QPixmap pixmap)
{
    // make this object focusable (able to receive input) & movable
    setFlag(QGraphicsPixmapItem::ItemIsFocusable);
    setFlag(QGraphicsPixmapItem::ItemIsMovable, false);

    // scale graphics
    QSize playerSize(40, 40);
    QPixmap scaledPixmap = pixmap.scaled(playerSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

    // center graphics
    setOffset(-scaledPixmap.width() / 2, -scaledPixmap.height() / 2);

    // set graphics
    setPixmap(scaledPixmap);

    qDebug() << "Player initialized\n";
}

void Player::setX(qreal x) {
    setPos(x, y());
}

void Player::move(qreal xPos) {
    // set moving speed depends on distant
    qreal distance = abs(xPos - x());
    qreal baseSpeed = 2; // more = slow

    int duration = static_cast<int>(distance * baseSpeed);

    // duration = std::max(100, std::min(duration, 1000)); // clamp between 100ms to 1000ms

    // make animation object to animate player moving
    animation = new QPropertyAnimation(this, "x");
    animation->setDuration(duration); // in ms
    animation->setStartValue(x());
    animation->setEndValue(xPos);
    animation->start();
}

void Player::shoot() {
    Bullet* bullet = new PlayerBullet(x(), y(), 1000.0);
    scene()->addItem(bullet);
    bullet->move();
}

