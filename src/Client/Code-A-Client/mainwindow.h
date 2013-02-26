#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
// #include <phonon/MediaSource>
// #include <phonon/MediaObject>
#include <QCoreApplication>
#include <QTcpSocket>
#include <QPixmap>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <list>
#include "../../GameData/Physics.hpp"
#include "../../GameData/Command.hpp"
#include "nm.h"
#include "game.h"
#include "gameview.h"
#include <QKeyEvent>
#include <QRect>
#include <QPolygon>
#include <QPoint>
#include <QLine>
#include <cmath>
#include <QWheelEvent>

class Nm;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    void NewGame();
    ~MainWindow();
    Ui::MainWindow *ui;
    // WARNING : arrows key cannot be used
    void keyReleaseEvent(QKeyEvent *);
    void keyPressEvent(QKeyEvent *);
    void setMove(int, int);
    
private slots:
    void Playagain();
    void on_loginb_pressed();

private:
//    Phonon::MediaObject *music;
    Nm *n;
    Game *game;
    GameView *view;
    bool ingame;
    int dvectorx;
    int dvectory;
};

#endif // MAINWINDOW_H


