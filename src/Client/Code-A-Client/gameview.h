#ifndef GAMEVUE_H
#define GAMEVUE_H

#include "mainwindow.h"

class Nm;

class GameView : public QGraphicsView
{
public:
    GameView(QWidget *);
    void mouseMoveEvent(QMouseEvent *);
    void bindNet(Nm *);
    Nm *n;
    int angle;
    int status;
    bool ingame;
    int dvectorx;
    int dvectory;
};

#endif // GAMEVUE_H
