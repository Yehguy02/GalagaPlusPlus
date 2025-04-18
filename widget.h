#ifndef WIDGET_H
#define WIDGET_H

#include "scene.h"

#include <QWidget>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void goHowToPlay();

private:
    void gameEndPage();

    QMediaPlayer* musicPlayer;
    QAudioOutput* audioOutput;
    QPushButton* playButton;
    QPushButton* howToPlayButton;
    QPushButton* backButton;
    QPushButton* mainMenuButton;
    Ui::Widget *ui;
    Scene* scene;
};
#endif // WIDGET_H
