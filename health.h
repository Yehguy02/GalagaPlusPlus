#ifndef HEALTH_H
#define HEALTH_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Health : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Health(QObject *parent = nullptr);
    ~Health();

signals:

private:

};

#endif // HEALTH_H
