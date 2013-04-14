#ifndef HUDRTS_H
#define HUDRTS_H

#include <QWidget>
#include <QLabel>
#include <QPalette>
#include <QString>
#include <QMouseEvent>
#include <QShowEvent>
#include <QtGui>
#include <iostream>
#include <QProgressBar>
#include <QTabWidget>

class HudRts : public QWidget
{
public:
    HudRts(QWidget *parent = 0);
    ~HudRts();
    void        affSelect(int decalageImgX, int decalageImgY, int decalageBarreX, int decalageBarreY);
    void        parssImg();

    QPalette    fontAffSelec;

    QLabel      *labelMiniMap;
    QWidget     *widgetAffSelec;
    QLabel      *imgMinion;
    int         nbrPage;
    QTabWidget  *tabsSelec;
    QProgressBar *barreVie;
    int         cptGene;
    int         cptX;
    int         cptY;
    int         decalageImgX;
    int         decalageImgY;
    int         decalageBarreX;
    int         decalageBarreY;
    int         numOnglet;
    QString     tmp;

protected:
    void        mousePressEvent(QMouseEvent *event);
};

#endif // HUDRTS_H
