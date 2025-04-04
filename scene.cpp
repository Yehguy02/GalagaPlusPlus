#include "scene.h"
#include "enemy.h"

#include <cmath>

Scene::Scene(QObject *parent)
    : QGraphicsScene(parent)
{
    // setup timer for spawning enemy
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Scene::spawnEnemy);

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

    // start the timer for enemy to spawn
    timer->start(3000);
}

void Scene::gameStop() {
    qDebug() << "WOOOOOOOOOOOOOOOOOOOO0000000000000000000000000000000000000000000 GAME END WOOOOOOOOOOOOOOOOOOOOOO0000000000000000000000000000000000000000000000000000";

    // stop enemy summon timer
    timer->stop();

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
    player->setPos(0, 350);
    player->setFocus(); // make player receive key event
}

void Scene::spawnEnemy() {
    int totalEnemy = QRandomGenerator::global()->bounded(5, 15);
    for (int i{0}; i < totalEnemy; i++) {
        qreal xPos = LEFTXPOS + (700.0 / (totalEnemy+1)) * (i+1);
        Enemy* e = new Enemy(this, xPos);
        addItem(e);
        connect(e, &Enemy::enemyHit, this, &Scene::gameStop);
        e->move();
    }
}


