#include "widget.h"
#include "./ui_widget.h"

#include <QGraphicsPixmapItem>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    // initialized new ui
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    // make the graphicsView take up full window & remove scroll bar
    ui->graphicsView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // set a specific screen size
    QSize screenSize(800,900);
    setFixedSize(screenSize);

    // create new scene and set pos & size
    scene = new Scene(this);
    scene->setSceneRect(ui->graphicsView->width() / -2, ui->graphicsView->height() / -2, ui->graphicsView->width(), ui->graphicsView->height());

    connect(scene, &Scene::gameEnded, this, &Widget::gameEndPage);

    // Set scene to the graphicsView
    ui->graphicsView->setScene(scene);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::gameEndPage() {
    ui->stackedWidget->setCurrentIndex(2);
}

void Widget::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    scene->gameStart();
}

void Widget::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

