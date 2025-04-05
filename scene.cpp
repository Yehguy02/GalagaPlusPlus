#include "scene.h"
#include "enemy.h"
#include "powerup.h"

#include <cmath>

Scene::Scene(QObject *parent)
    : QGraphicsScene(parent)
{
    // setup timer for spawning enemy
    enemyTimer = new QTimer(this);
    connect(enemyTimer, &QTimer::timeout, this, &Scene::spawnEnemy);

    // set up timer for spawning power up
    powerUpTimer = new QTimer(this);
    connect(powerUpTimer, &QTimer::timeout, this, &Scene::spawnBuff);

    qDebug() << "scene created";
}

Scene::~Scene() {

}

void Scene::gameStart() {
    // Create background
    QPixmap bgPixmap(":/images/space background.png");
    QSize screenSize(800,900);
    QPixmap scaledPixmap = bgPixmap.scaled(screenSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

    // Create the pixmap item with the scaled image
    QGraphicsPixmapItem* pixItem = new QGraphicsPixmapItem(scaledPixmap);
    addItem(pixItem);

    // Center the image in the scene
    pixItem->setPos(-scaledPixmap.width() / 2, -scaledPixmap.height() / 2);

    // set player
    setPlayer();

    // start the timers
    enemyTimer->start(3000);
    powerUpTimer->start(12000);
}

void Scene::gameStop() {
    qDebug() << "WOOOOOOOOOOOOOOOOOOOO0000000000000000000000000000000000000000000 GAME END WOOOOOOOOOOOOOOOOOOOOOO0000000000000000000000000000000000000000000000000000";

    // stop timers
    enemyTimer->stop();
    powerUpTimer->stop();

    // remove & delete all object in scene
    QList<QGraphicsItem*> itemList = items();
    for (QGraphicsItem* item : itemList) {
        // to prevent double delete error when deleteing inheritance of QObject + QGraphicsItem
        QObject* obj = dynamic_cast<QObject*>(item);
        if (obj) {
            obj->deleteLater();
        } else {
            delete(item);
        }
    }

    emit Scene::gameEnded();
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    // get mouse x position
    qreal mouseX = event->scenePos().x();

    // set player pos to mouseX position
    player->move(mouseX);

    // default handling
    QGraphicsScene::mousePressEvent(event);
}

void Scene::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Space && !event->isAutoRepeat()) {
        player->shoot();
    }
}

void Scene::setPlayer() {
    player = new Player(QPixmap(":/images/spaceship.png"));
    addItem(player);
    connect(player, &Player::playerDied, this, &Scene::gameStop);
    player->setPos(0, 350);
    player->setFocus(); // make player receive key event
    player->displayHealth();
}

void Scene::spawnEnemy() {
    int totalEnemy = QRandomGenerator::global()->bounded(5, 15);
    for (int i{0}; i < totalEnemy; i++) {
        qreal xPos = LEFTXPOS + (700.0 / (totalEnemy+1)) * (i+1);
        Enemy* e = new Enemy(this, xPos);
        addItem(e);
        connect(e, &Enemy::enemyHit, this, &Scene::playerTookDamage);
        e->move();
    }
}

void Scene::spawnBuff() {
    int randomInt = QRandomGenerator::global()->bounded(0, 701);

    PowerUp* power = new PowerUp(player);
    addItem(power);
    power->setPos(randomInt - 350, -600);
    power->move();
}

void Scene::playerTookDamage() {
    if (!player) return;

    player->receiveDamage();
}


