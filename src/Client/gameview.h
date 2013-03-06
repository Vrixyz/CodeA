#ifndef GAMEVUE_H
#define GAMEVUE_H

#include "game.h"

class Nm;

class GameView : public QGraphicsView
{
public:
    GameView(QWidget *parent = 0);
    void keyReleaseEvent(QKeyEvent *);
    void keyPressEvent(QKeyEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *);
    void setMove(int, int);
    void rotationUpdate();
    void bindNet(Nm *);
    Nm *n;
    QPoint base;
    QRect selecrect;
    QPoint cur;
    QRubberBand *rubberBand;
    bool baseknown;
    int cangle;
    int angle;
    int status;
    int dvectorx;
    int dvectory;
};

#endif // GAMEVUE_H
