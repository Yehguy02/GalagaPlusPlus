#include "health.h"

Health::Health(QObject *parent)
    : QObject{parent}
{
    // scaled pixmap
    QPixmap pixmap = QPixmap(":/images/heart.png");
    QSize heartSize(40, 40);
    QPixmap scaledPixmap = pixmap.scaled(heartSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

    // set pivot to be centered
    setOffset(-scaledPixmap.width() / 2, -scaledPixmap.height() / 2);

    // set graphics
    setPixmap(scaledPixmap);

    // qDebug() << "Health initialize";
}

Health::~Health() {
    qDebug() << "Ughhasfusaeni, you took 1 daage";
}
