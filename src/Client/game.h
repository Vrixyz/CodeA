#ifndef GAME_H
#define GAME_H

#include <QGraphicsItem>
#include <QLabel>
#include <QTextEdit>
#include <QListWidget>
#include <QDialog>
#include <QLineEdit>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMainWindow>
#include <QPushButton>
#include <QKeyEvent>
#include <QRect>
#include <QPolygon>
#include <QPoint>
#include <QLine>
#include <QWheelEvent>
#include <QRubberBand>
#include <cmath>
#include <iostream>
#include "../GameData/World.hpp"
#include "../GameData/Physics.hpp"
#include "../GameData/Unit.hpp"
#include "../GameData/Bullet.hpp"
#include "../GameData/Element.hpp"
#include "../GameData/Information.hpp"
#include "../GameData/Command.hpp"
#include "gameview.h"
#include "nm.h"
#include "element.h"
#include "bullet.h"
#include "unit.h"
#include "MyWindow.h"
#include "hudrts.h"
#include "HudShooter.h"

class GameView;
class Element;
class Bullet;
class Unit;
class MyWindow;

class Game
{
public:

    Game(const std::string &, unsigned int , const std::string &, MyWindow *parent = 0);
    ~Game();
    void drawWorld();
    void setPlayerDefinition(const GameData::Information::PlayerDefinition &);
    void setSelection(int unitId);
    void setWorld(GameData::World);
    int angle;
    GameData::World getWorld();
    std::list<Element *> e;
    std::list<Bullet *> b;
    std::list<Unit *> u;
    std::list<unsigned int> idList;
    GameView *view;
    HudShooter *huds;
    HudRts *hudr;
    Nm *n;
    QGraphicsScene *scene;
    MyWindow *win;
    bool isRTS;
    GameData::Information::PlayerDefinition* playerDefinition;
    unsigned int selectedUnit;
private:
    GameData::World world;
};

#endif // GAME_H
