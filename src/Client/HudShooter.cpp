#include "HudShooter.h"

HudShooter::HudShooter(QWidget *parent) :
    QWidget(parent)
{
    concatAtack = "";
    concatResMag = "";
    concatResPhys = "";
    concatVitesse = "";
    concatVie = "";
    concatMana = "";
    nbrKill = 0;
    nbrAssist = 0;
    nbrDeath = 0;
    nbrAttack = 70;
    nbrResMag = 30;
    nbrResPhys = 30;
    nbrVitesse = 0.735;
    compteur = 0;
    vieDepart = 100;
    manaDepart = 100;
    vieDepartEnnemis = 100;
    manaDepartEnnemis = 100;
    cpt = 0;

    setGeometry(0, 0, 800, 600);
    setFixedSize(800, 600);
    setFocusPolicy(Qt::NoFocus);
    createMinimap();
    createScore();
    createInfoPerso();
    createSortLifeMana();
    createInfoEnnemis();
}

void    HudShooter::createMinimap()
{
    labelMiniMap = new QLabel(this);
    labelMiniMap->setGeometry(0, 350, 250, 250);
    labelMiniMap->setPixmap(QPixmap("./img/mini_map.png"));

}

void    HudShooter::createScore()
{
    fontScore.setColor(QPalette::Window, Qt::black);
    fontScore.setColor(QPalette::WindowText, Qt::white);

    labelScore = new QLabel(this);
    labelScore->setGeometry(500, 0, 270, 25);
    labelScore->setAutoFillBackground(true);
    labelScore->setPalette(fontScore);

    imgKill = new QLabel(labelScore);
    imgKill->setGeometry(0, 0, 25, 25);
    imgKill->setPixmap(QPixmap("./img/epeeKill.png"));

    imgAssist = new QLabel(labelScore);
    imgAssist->setGeometry(100, 0, 25, 25);
    imgAssist->setPixmap(QPixmap("./img/assist.png"));

    imgDeath = new QLabel(labelScore);
    imgDeath->setGeometry(200, 0, 25, 25);
    imgDeath->setPixmap(QPixmap("./img/teteMort.png"));

    labelNbrKill = new QLabel(labelScore);
    labelNbrKill->setGeometry(30, 0, 40, 25);
    tmp = QString::number(nbrKill);
    labelNbrKill->setText(tmp);

    labelNbrAssist = new QLabel(labelScore);
    labelNbrAssist->setGeometry(130, 0, 40, 25);
    tmp = QString::number(nbrAssist);
    labelNbrAssist->setText(tmp);

    labelNbrDeath = new QLabel(labelScore);
    labelNbrDeath->setGeometry(230, 0, 40, 25);
    tmp = QString::number(nbrDeath);
    labelNbrDeath->setText(tmp);
}

void    HudShooter::createInfoPerso()
{
    fontInfoPerso.setColor(QPalette::WindowText, Qt::white);

    labelInfoPerso = new QLabel(this);
    labelInfoPerso->setGeometry(650, 450, 150, 150);
    labelInfoPerso->setPixmap(QPixmap("./img/grass.png"));
    labelInfoPerso->setPalette(fontInfoPerso);

    labelAttackPerso = new QLabel(labelInfoPerso);
    labelAttackPerso->setGeometry(0, 10, 150, 25);
    tmp = QString::number(nbrAttack);
    concatAtack = "      Attaque:    " + tmp;
    labelAttackPerso->setText(concatAtack);

    labelResMagPerso = new QLabel(labelInfoPerso);
    labelResMagPerso->setGeometry(0, 40, 150, 25);
    tmp = QString::number(nbrResMag);
    concatResMag = "      Res Mag:    " + tmp;
    labelResMagPerso->setText(concatResMag);

    labelResPhysPerso = new QLabel(labelInfoPerso);
    labelResPhysPerso->setGeometry(0, 70, 150, 25);
    tmp = QString::number(nbrResPhys);
    concatResPhys = "      Res Phys:    " + tmp;
    labelResPhysPerso->setText(concatResPhys);

    labelVitessePerso = new QLabel(labelInfoPerso);
    labelVitessePerso->setGeometry(0, 100, 150, 25);
    tmp = QString::number(nbrVitesse);
    concatVitesse = "      Vitesse:    " + tmp;
    labelVitessePerso->setText(concatVitesse);
}

void    HudShooter::createSortLifeMana()
{
    fontSortLM.setColor(QPalette::Window, Qt::black);
    labeleSortLM = new QLabel(this);
    labeleSortLM->setGeometry(300, 500, 300, 200);
    labeleSortLM->setAutoFillBackground(true);
    labeleSortLM->setPalette(fontSortLM);

    QPushButton *sort1 = new QPushButton("Sort 1", labeleSortLM);
    sort1->setGeometry(0, 0, 60, 60);
    QPushButton *sort2 = new QPushButton("Sort 2", labeleSortLM);
    sort2->setGeometry(60, 0, 60, 60);
    QPushButton *sort3 = new QPushButton("Sort 3", labeleSortLM);
    sort3->setGeometry(120, 0, 60, 60);
    QPushButton *sort4 = new QPushButton("Sort 4", labeleSortLM);
    sort4->setGeometry(180, 0, 60, 60);
    QPushButton *sort5 = new QPushButton("Sort 5", labeleSortLM);
    sort5->setGeometry(240, 0, 60, 60);

    barreVie = new QProgressBar(labeleSortLM);
    barreVie->setGeometry(0, 60, 300, 20);
    barreVie->setValue(vieDepart);
    tmpVie = QString::number(vieDepart);
    concatVie = "Vie: " + tmpVie + "/ 100";
    barreVie->setFormat(concatVie);

    barreMana = new QProgressBar(labeleSortLM);
    barreMana->setGeometry(0, 80, 300, 20);
    barreMana->setValue(manaDepart);
    tmpMana = QString::number(manaDepart);
    concatMana = "Mana: " + tmpMana + "/ 100";
    barreMana->setFormat(concatMana);
}

void    HudShooter::createInfoEnnemis()
{
    labelInfoEnnemis = new QLabel(this);
    labelInfoEnnemis->setGeometry(0, 0, 200, 50);
    labelImgEnnemis = new QLabel(labelInfoEnnemis);
    labelImgEnnemis->setGeometry(0, 0, 150, 50);
    labelImgEnnemis->setPixmap(QPixmap("./img/minionbasicmelee.png"));

    barreVieEnnemis = new QProgressBar(labelInfoEnnemis);
    barreVieEnnemis->setGeometry(50, 0, 150,25);
    barreVieEnnemis->setValue(vieDepartEnnemis);
    tmpVieEnnemis = QString::number(vieDepartEnnemis);
    concatVieEnnemis = "Vie: " + tmpVieEnnemis + "/ 100";
    barreVieEnnemis->setFormat(concatVieEnnemis);

    barreManaEnnemis = new QProgressBar(labelInfoEnnemis);
    barreManaEnnemis->setGeometry(50, 25, 150,25);
    barreManaEnnemis->setValue(manaDepartEnnemis);
    tmpManaEnnemis = QString::number(manaDepartEnnemis);
    concatManaEnnemis = "Mana: " + tmpManaEnnemis + "/ 100";
    barreManaEnnemis->setFormat(concatManaEnnemis);
}

void    HudShooter::clickInfoPerso(QMouseEvent *event)
{
    nbrAttack = event->pos().x();
    nbrResMag = event->pos().y();
    nbrResPhys = nbrAttack + nbrResMag;
    nbrVitesse = nbrAttack - nbrResMag;

    tmp = QString::number(nbrAttack);
    concatAtack = "      Attaque:    " + tmp;
    labelAttackPerso->setText(concatAtack);
    tmp = QString::number(nbrResMag);
    concatResMag = "      Res Mag:    " + tmp;
    labelResMagPerso->setText(concatResMag);
    tmp = QString::number(nbrResPhys);
    concatResPhys = "      Res Phy:    " + tmp;
    labelResPhysPerso->setText(concatResPhys);
    tmp = QString::number(nbrVitesse);
    concatVitesse = "      Vitesse:    " + tmp;
    labelVitessePerso->setText(concatVitesse);
}

void    HudShooter::clickLifeMana()
{
    vieDepart -= 20;
    manaDepart -= 10;
    if (vieDepart == 0)
        vieDepart = 100;
    if (manaDepart == 0)
        manaDepart = 100;

    barreVie->setValue(vieDepart);
    barreMana->setValue(manaDepart);
    tmpVie = QString::number(vieDepart);
    concatVie = "Vie: " + tmpVie + "/ 100";
    barreVie->setFormat(concatVie);
    tmpMana = QString::number(manaDepart);
    concatMana = "Mana: " + tmpMana + "/ 100";
    barreMana->setFormat(concatMana);
}

void    HudShooter::clickScore()
{
    cpt++;
    if (((cpt % 3) == 0) && cpt != 0)
    {
        nbrKill += 3;
        tmp = QString::number(nbrKill);
        labelNbrKill->setText(tmp);
    }
    if ((cpt % 6 == 0) && cpt != 0)
    {
        nbrAssist += 1;
        tmp = QString::number(nbrAssist);
        labelNbrAssist->setText(tmp);
    }
    if ((nbrAssist % 4 == 0) && nbrAssist != 0)
    {
        nbrDeath += 4;
        tmp = QString::number(nbrDeath);
        labelNbrDeath->setText(tmp);
    }
}

void    HudShooter::clickEnnemisInfo()
{
    vieDepartEnnemis -= 20;
    manaDepartEnnemis -= 10;
    if (vieDepartEnnemis == 0)
        vieDepartEnnemis = 100;
    if (manaDepartEnnemis == 0)
        manaDepartEnnemis = 100;

    barreVieEnnemis->setValue(vieDepartEnnemis);
    barreManaEnnemis->setValue(manaDepartEnnemis);
    tmpVieEnnemis = QString::number(vieDepartEnnemis);
    concatVieEnnemis = "Vie: " + tmpVieEnnemis + "/ 100";
    barreVieEnnemis->setFormat(concatVieEnnemis);
    tmpManaEnnemis = QString::number(manaDepartEnnemis);
    concatManaEnnemis = "Mana: " + tmpManaEnnemis + "/ 100";
    barreManaEnnemis->setFormat(concatManaEnnemis);
}

HudShooter::~HudShooter()
{
}
