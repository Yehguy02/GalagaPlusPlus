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
    QSize screenSize(800,800);
    setFixedSize(screenSize);

    // create new scene and set pos & size
    scene = new Scene(this);
    scene->setSceneRect(ui->graphicsView->width() / -2, ui->graphicsView->height() / -2, ui->graphicsView->width(), ui->graphicsView->height());

    connect(scene, &Scene::gameEnded, this, &Widget::gameEndPage);

    // // set menu screen
    // background
    QPixmap bg = QPixmap(":/images/menu background.png").scaled(screenSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    ui->label->setPixmap(bg);
    ui->label->setScaledContents(true);
    ui->label->resize(screenSize);
    ui->label->move(0,0);

    // how to play graphics
    QPixmap howtoplay = QPixmap(":/images/how to play.png").scaled(screenSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    ui->label_3->setPixmap(howtoplay);
    ui->label_3->setScaledContents(true);
    ui->label_3->resize(screenSize);
    ui->label_3->move(0,0);

    // game over graphics
    QPixmap gameOver = QPixmap(":/images/game over.png").scaled(screenSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    ui->label_4->setPixmap(gameOver);
    ui->label_4->setScaledContents(true);
    ui->label_4->resize(screenSize);
    ui->label_4->move(0,0);

    // logo
    QPixmap logo = QPixmap(":/images/galaga png.png").scaled(QSize(100,100), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    ui->label_2->setPixmap(logo);
    ui->label_2->setScaledContents(true);
    ui->label_2->resize(QSize(300,300));
    ui->label_2->move(250,0);

    // play button
    playButton = new QPushButton("START GAME", this);
    playButton->setGeometry(100, 100, 200, 50); // position and size of the button
    connect(playButton, &QPushButton::clicked, this, &Widget::on_pushButton_clicked);
    playButton->move(300, 300);

    // how to play button
    howToPlayButton = new QPushButton("How To Play", this);
    howToPlayButton->setGeometry(100, 100, 200, 50);
    howToPlayButton->move(300, 400);
    connect(howToPlayButton, &QPushButton::clicked, this, &Widget::goHowToPlay);

    // back button
    backButton = new QPushButton("back", this);
    backButton->setGeometry(100, 100, 100, 50);
    backButton->move(50, 700);
    connect(backButton, &QPushButton::clicked, this, &Widget::on_pushButton_3_clicked);
    backButton->setDisabled(true);
    backButton->hide();

    // main menu button
    mainMenuButton = new QPushButton("MAIN MENU", this);
    mainMenuButton->setGeometry(100, 100, 200, 50);
    mainMenuButton->move(300, 500);
    connect(mainMenuButton, &QPushButton::clicked, this, &Widget::on_pushButton_2_clicked);
    mainMenuButton->setDisabled(true);
    mainMenuButton->hide();

    // Set scene to the graphicsView
    ui->graphicsView->setScene(scene);

    // set up music player
    musicPlayer = new QMediaPlayer();
    audioOutput = new QAudioOutput();
    musicPlayer->setAudioOutput(audioOutput);
    audioOutput->setVolume(0.5);
    musicPlayer->setSource(QUrl("qrc:/sounds/waludu dan dan danali.mp3"));
    musicPlayer->play();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::gameEndPage() {
    ui->stackedWidget->setCurrentIndex(2);
    musicPlayer->stop();

    playButton->setDisabled(true);
    playButton->hide();
    howToPlayButton->setDisabled(true);
    howToPlayButton->hide();
    backButton->setDisabled(true);
    backButton->hide();
    mainMenuButton->setDisabled(false);
    mainMenuButton->show();
}

void Widget::on_pushButton_clicked()
{
    playButton->setDisabled(true);
    playButton->hide();
    howToPlayButton->setDisabled(true);
    howToPlayButton->hide();
    backButton->setDisabled(true);
    backButton->hide();
    mainMenuButton->setDisabled(true);
    mainMenuButton->hide();

    ui->stackedWidget->setCurrentIndex(1);
    scene->gameStart();
    musicPlayer->stop();

    // set game music
    musicPlayer->setSource(QUrl("qrc:/sounds/linggang guli guli.mp3"));
    musicPlayer->play();
}

void Widget::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    musicPlayer->stop();

    // set main menu music
    musicPlayer->setSource(QUrl("qrc:/sounds/waludu dan dan danali.mp3"));
    musicPlayer->play();
    playButton->setDisabled(false);
    playButton->show();
    howToPlayButton->setDisabled(false);
    howToPlayButton->show();
    backButton->setDisabled(true);
    backButton->hide();
    mainMenuButton->setDisabled(true);
    mainMenuButton->hide();
}

void Widget::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

    playButton->setDisabled(false);
    playButton->show();
    howToPlayButton->setDisabled(false);
    howToPlayButton->show();
    backButton->setDisabled(true);
    backButton->hide();
    mainMenuButton->setDisabled(true);
    mainMenuButton->hide();
}

void Widget::goHowToPlay() {
    ui->stackedWidget->setCurrentIndex(3);

    playButton->setDisabled(true);
    playButton->hide();
    howToPlayButton->setDisabled(true);
    howToPlayButton->hide();
    backButton->setDisabled(false);
    backButton->show();
    mainMenuButton->setDisabled(true);
    mainMenuButton->hide();
}

