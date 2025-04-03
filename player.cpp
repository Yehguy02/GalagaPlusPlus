#include "player.h"

Player::Player(QPixmap pixmap)
{
    // make this object focusable (able to receive input) & movable
    setFlag(QGraphicsPixmapItem::ItemIsFocusable);
    setFlag(QGraphicsPixmapItem::ItemIsMovable);

    // scale graphics
    QSize playerSize(40, 40);
    QPixmap scaledPixmap = pixmap.scaled(playerSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

    // center graphics
    setOffset(-scaledPixmap.width() / 2, -scaledPixmap.height() / 2);

    // set graphics
    setPixmap(scaledPixmap);

    qDebug() << "Player initialized\n";
}

