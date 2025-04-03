#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>

#include <QDebug>

class Player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF position READ pos WRITE setPos)
public:
    explicit Player(QPixmap pixmap);

signals:

protected:

private:
};

#endif // PLAYER_H
