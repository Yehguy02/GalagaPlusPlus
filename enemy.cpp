#include "enemy.h"
#include "enemybullet.h"
#include "player.h"

Enemy::Enemy(Scene* scene, qreal xPos)
    : xPos(xPos), scene(scene)
{
    // randomize graphics for enemy
    int randomGraphicsIndex = QRandomGenerator::global()->bounded(1,5);
    QString path = ":/images/enemy" + QString::number(randomGraphicsIndex) + ".png";
    QPixmap graphics((QPixmap(path)));

    // set enemy size
    QSize enemySize(60, 60);
    QPixmap scaledPixmap = graphics.scaled(enemySize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

    // set graphics
    setOffset(-scaledPixmap.width() / 2, -scaledPixmap.height());
    setPixmap(scaledPixmap);

    // set initial enemy position
    setPos(xPos, -600);

    // make enemy shoot bullet at random time (1 - 3 second interval)
    timer = new QTimer(this);
    int min = 1000;
    int max = 3000;
    int randomInt = QRandomGenerator::global()->bounded(min, max+1);

    connect(timer, &QTimer::timeout, this, &Enemy::shootBullet);
    timer->start(randomInt);

    qDebug() << "enemy created";
}

Enemy::~Enemy() {
    qDebug() << "Enemy dead";
    delete(timer);
}

void Enemy::setY(qreal y) {
    setPos(x(), y);

    if (collide()) {
        emit Enemy::enemyHit();
        delete(this);
    }
}

void Enemy::move() {
    // do the animation
    animation = new QPropertyAnimation(this, "y");
    animation->setDuration(15000); // in ms
    animation->setStartValue(-600.0);
    animation->setEndValue(500.0);

    connect(animation, &QPropertyAnimation::finished, [=]() {
        scene->removeItem(this);
        delete(this);
    });

    animation->start();
}

void Enemy::shootBullet() {
    EnemyBullet* bullet = new EnemyBullet(x(), y());
    scene->addItem(bullet);
    connect(bullet, &EnemyBullet::enemyBulletHit, scene, &Scene::gameStop);
    bullet->move();
}

bool Enemy::collide() {
    QList<QGraphicsItem*> collideItems = collidingItems();
    for (QGraphicsItem* item : collideItems) {
        Player* p = dynamic_cast<Player*>(item);
        if (p) return true;
    }
    return false;
}
