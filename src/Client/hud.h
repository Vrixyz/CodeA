#ifndef HUD_H
#define HUD_H

#include <QLabel>
#include <QPixmap>
#include <QFrame>
#include <QWidget>
#include <iostream>
#include "mainwindow.h"

class Hud
{
public:
    Hud();
    ~Hud();

    QWidget *winHud;
    QWidget *minimap;
    QWidget *infoPerso;
    QWidget *winScore;
    QWidget *sortLifeMana;
    QWidget *lifeMana;
    QWidget *barSorts;

    QPalette fontInfoPerso;
    QPalette fontScore;
    QPalette fontLife;

    QLabel *imgMap;
    QLabel *BackgroundInfo;
    QLabel *persoInfo;
    QLabel *score;
    QLabel *life;
    QLabel *barreLifeMana;
    QLabel *sortsBar;
};

#endif // HUD_H
