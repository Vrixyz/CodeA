#ifndef HUDSHOOTER_H
#define HUDSHOOTER_H

#include <QWidget>
#include <QLabel>
#include <QPalette>
#include <QString>
#include <QMouseEvent>
#include <QtGui>
#include <QProgressBar>
#include <QPushButton>
#include <QTabWidget>

class HudShooter : public QWidget
{
public:
    HudShooter(QWidget *parent = 0);
    ~HudShooter();

    void        createMinimap();
    void        createScore();
    void        createInfoPerso();
    void        createSortLifeMana();

    void        clickInfoPerso(QMouseEvent *event);
    void        clickLifeMana();
    void        clickScore();
    void        clickEnnemisInfo();

    void        createInfoEnnemis();

    QPalette    fontScore;
    QPalette    fontInfoPerso;
    QPalette    fontSortLM;

    QLabel      *labelMiniMap;

    QLabel      *labelScore;
    QLabel      *imgKill;
    QLabel      *imgAssist;
    QLabel      *imgDeath;
    QLabel      *labelNbrKill;
    QLabel      *labelNbrAssist;
    QLabel      *labelNbrDeath;

    QLabel      *labelInfoPerso;
    QLabel      *labelAttackPerso;
    QLabel      *labelResMagPerso;
    QLabel      *labelResPhysPerso;
    QLabel      *labelVitessePerso;
    
    QLabel      *labeleSortLM;
    QLabel      *labelAffVie;
    QProgressBar *barreVie;
    QProgressBar *barreMana;

    QLabel      *labelInfoEnnemis;
    QLabel      *labelImgEnnemis;
    QProgressBar *barreVieEnnemis;
    QProgressBar *barreManaEnnemis;

    int         nbrKill;
    int         nbrAssist;
    int         nbrDeath;

    int         nbrAttack;
    int         nbrResMag;
    int         nbrResPhys;
    float       nbrVitesse;

    int         vieDepart;
    int         manaDepart;
    int         compteur;

    int         vieDepartEnnemis;
    int         manaDepartEnnemis;

    QString     tmp;
    QString     concatAtack;
    QString     concatResMag;
    QString     concatResPhys;
    QString     concatVitesse;

    QString     tmpVie;
    QString     concatVie;
    QString     tmpMana;
    QString     concatMana;

    int         cpt;

    QString     tmpVieEnnemis;
    QString     concatVieEnnemis;
    QString     tmpManaEnnemis;
    QString     concatManaEnnemis;
};

#endif // HUDSHOOTER_H
