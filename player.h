#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class Player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)
public:
    explicit Player(QPixmap pixmap);

    void move(qreal xPos);
    void shoot();

public slots:
    void setX(qreal x);

signals:

protected:

private:
    QPropertyAnimation* animation;
    // void playerShoot();
    // void keyPressEvent(QKeyEvent* event) override;
};

#endif // PLAYER_H
