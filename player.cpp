#include "player.h"
#include "playerbullet.h"

Player::Player(QPixmap pixmap)
{
    // set player initial speed
    speed = 2;

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

    // set health to be defalut (10);
    for (int i{0}; i < 10; i++) {
        health.push_back(new Health());
    }

    qDebug() << "Player initialized\n";
}

void Player::setX(qreal x) {
    setPos(x, y());
}

void Player::move(qreal xPos) {
    // set moving speed depends on distant
    qreal distance = abs(xPos - x());
    qreal baseSpeed = speed; // more = slow

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

void Player::displayHealth() {
    for (int i{0}; i< health.size(); i++) {
        int yPos = -350 + (40 * i);
        scene()->addItem(health[i]);
        health[i]->setPos(-375, yPos);
    }
}

void Player::receiveDamage() {
    if (health.size() > 1) {
        Health* heart = health.takeLast();
        delete(heart);
    } else {
        emit playerDied();
    }
}

void Player::receiveHeal() {
    if (health.size() < 10) {
        Health* heart = new Health();
        health.push_back(heart);

        // set new heart pos
        int yPos = -350 + (40 * (health.size() - 1));
        scene()->addItem(heart);
        heart->setPos(-375, yPos);
    } else {
        qDebug() << "You have full health0";
    }
}

void Player::rapidFire() {
    QTimer* rapidTimer = new QTimer(this);
    connect(rapidTimer, &QTimer::timeout, this, &Player::shoot);
    rapidTimer->start(10);

    // make the timer last for 5 second
    QTimer::singleShot(5000, this, [=]{
        rapidTimer->stop();
        qDebug() << "rapid timer stop";
    });
}

void Player::speedBoost() {
    speed = 1;
    QTimer::singleShot(5000, this, [=]{
        speed = 2;
        qDebug() << "sapeed boost is over";
    });
}

