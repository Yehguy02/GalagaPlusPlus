#include "widget.h"
#include "player.h"
#include "./ui_widget.h"

#include <QGraphicsPixmapItem>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    // initialized new ui
    ui->setupUi(this);

    // make the graphicsView take up full window & remove scroll bar
    ui->graphicsView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // set a specific screen size
    QSize screenSize(800,900);
    setFixedSize(screenSize);

    // create new scene and set pos & size
    scene = new Scene(this);
    scene->setSceneRect(ui->graphicsView->width() / -2, ui->graphicsView->height() / -2, ui->graphicsView->width(), ui->graphicsView->height());

    // Load and scale the image
    QPixmap bgPixmap(":/images/space background.png");
    QPixmap scaledPixmap = bgPixmap.scaled(screenSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

    // Create the pixmap item with the scaled image
    QGraphicsPixmapItem* pixItem = new QGraphicsPixmapItem(scaledPixmap);
    scene->addItem(pixItem);

    // Center the image in the scene
    pixItem->setPos(-scaledPixmap.width() / 2, -scaledPixmap.height() / 2);

    // draw line used for positioning objects (will delete later)
    scene->addLine(-400,0,400,0, QPen(Qt::white));
    scene->addLine(0,-500,0,500, QPen(Qt::white));

    // Create and add player into scene
    Player* player = new Player(QPixmap(":/images/spaceship.png"));
    scene->addItem(player);
    scene->setPlayer(player);

    // set player to the low position
    player->setPos(0, 350);

    // make player receive key event
    player->setFocus();

    // Set scene to the graphicsView
    ui->graphicsView->setScene(scene);
}

Widget::~Widget()
{
    delete ui;
}

