#include "hudrts.h"

HudRts::HudRts(QWidget *parent) :
    QWidget(parent)
{
    cptGene = 0;
    cptX = 0;
    cptY = 0;
    nbrPage = 0;
    decalageImgX = 20;
    decalageImgY = 40;
    decalageBarreX = 20;
    decalageBarreY = 80;
    numOnglet = 0;
    setGeometry(0, 0, 800, 600);
    setFixedSize(800, 600);
    setFocusPolicy(Qt::NoFocus);

    fontAffSelec.setColor(QPalette::Window, Qt::red);
    widgetAffSelec = new QWidget(this);
    widgetAffSelec->setGeometry(250,450, 400, 150);
    widgetAffSelec->setPalette(fontAffSelec);

    labelMiniMap = new QLabel(this);
    labelMiniMap->setGeometry(0, 350, 250, 250);
    labelMiniMap->setPixmap(QPixmap("./img/mini_map.png"));

//    tabs->addTab(imgMinion2, "2");
//    tabs->addTab(imgMinion3, "3");

//    QLabel  *imgMinion2 = new QLabel(widgetAffSelec);
//    imgMinion2->setPixmap(QPixmap("./img/purpleMinion.png"));
//    imgMinion2->setGeometry(45, 40, 40, 40);

//    QProgressBar *barreVie2 = new QProgressBar(widgetAffSelec);
//    barreVie2->setGeometry(45, 80, 40, 10);
//    barreVie2->setValue(100);

//    QLabel  *imgMinion3 = new QLabel(widgetAffSelec);
//    imgMinion3->setPixmap(QPixmap("./img/purpleMinion.png"));
//    imgMinion3->setGeometry(0, 95, 40, 40);

//    QProgressBar *barreVie3 = new QProgressBar(widgetAffSelec);
//    barreVie3->setGeometry(0, 135, 40, 10);
//    barreVie3->setValue(100);

}

void    HudRts::parssImg()
{
    if (cptX != 1 && cptY == 0)
    {
        decalageImgX += 45;
        decalageImgY += 0;
        decalageBarreX += 45;
        decalageBarreY += 0;
    }
    if (cptX == 9)
    {
        cptX = 1;
        cptY += 1;
        decalageImgX = 20;
        decalageImgY = 95;
        decalageBarreX = 20;
        decalageBarreY = 135;
    }
    if (cptX != 1 && cptY == 1)
    {
        decalageImgX += 45;
        decalageImgY += 0;
        decalageBarreX += 45;
        decalageBarreY += 0;
    }
}

void    HudRts::affSelect(int decalageImgX, int decalageImgY, int decalageBarreX, int decalageBarreY)
{
    imgMinion = new QLabel(tabsSelec);
    imgMinion->setPixmap(QPixmap("./img/purpleMinion.png"));
    imgMinion->setGeometry(decalageImgX, decalageImgY, 40, 40);
    imgMinion->show();

    barreVie = new QProgressBar(tabsSelec);
    barreVie->setGeometry(decalageBarreX, decalageBarreY, 40, 10);
    barreVie->setValue(100);
    barreVie->show();
}

HudRts::~HudRts()
{
}
