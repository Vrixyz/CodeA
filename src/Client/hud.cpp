#include "hud.h"

Hud::Hud()
{
    this->winHud = new QWidget();
    this->winHud->setGeometry(0, 0, 800, 600);

    this->minimap = new QWidget(winHud);
    this->minimap->setGeometry(0, 400, 200, 200);

    this->infoPerso = new QWidget(winHud);
    this->infoPerso->setGeometry(650, 450, 150, 150);

    this->winScore = new QWidget(winHud);
    this->winScore->setGeometry(600, 0, 200, 50);

    this->sortLifeMana = new QWidget(winHud);
    this->sortLifeMana->setGeometry(250, 500, 350, 100);

    this->lifeMana = new QWidget(winHud);
    this->lifeMana->setGeometry(250, 550, 350, 50);

    this->barSorts = new QWidget(winHud);
    this->barSorts->setGeometry(250, 500, 350, 50);

    this->fontInfoPerso.setColor(QPalette::WindowText, Qt::white);
    this->fontScore.setColor(QPalette::Window, Qt::yellow);
    this->fontScore.setColor(QPalette::WindowText, Qt::black);

    this->fontLife.setColor(QPalette::Window, Qt::blue);

    this->imgMap = new QLabel(this->minimap);
    this->imgMap->setPixmap(QPixmap("/home/tarik/HUD_PFA/mini_map.png"));
    this->imgMap->setFixedSize(200, 200);

    this->BackgroundInfo = new QLabel(this->infoPerso);
    this->BackgroundInfo->setPixmap(QPixmap("/home/tarik/HUD_PFA/grass.png"));

    this->persoInfo = new QLabel(this->infoPerso);
    this->persoInfo->setPalette(fontInfoPerso);
    this->persoInfo->setContentsMargins(5, 5, 5, 5);
    this->persoInfo->setText("\n     Attaque: 75\n     Armure: 30\n    RM: 30\n    Vitesse:0.750\n    V.dep: 350");

    this->score = new QLabel(this->winScore);
    this->score->setAutoFillBackground(true);
    this->score->setPalette(fontScore);
    this->score->setContentsMargins(5, 5, 5, 5);
    this->score->setText("Kill: 3     Death: 1        Assist: 2");

    this->life = new QLabel(this->sortLifeMana);
    this->life->setPalette(fontLife);
    this-> life->setFixedSize(350, 100);

    this->barreLifeMana = new QLabel(this->lifeMana);
    this->barreLifeMana->setPixmap(QPixmap("/home/tarik/HUD_PFA/manaLife.png"));
    this->barreLifeMana->setFixedSize(350, 50);

    this->sortsBar = new QLabel(this->barSorts);
    this->sortsBar->setPixmap(QPixmap("/home/tarik/HUD_PFA/SortInvoc.png"));
    this->sortsBar->setFixedSize(350, 50);

    this->winHud->show();
}

Hud::~Hud()
{

}
