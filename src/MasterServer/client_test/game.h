#ifndef GAME_H
#define GAME_H

#include "../../GameData/World.hpp"
#include "../../GameData/Physics.hpp"
#include "../../GameData/Unit.hpp"
#include "../../GameData/Bullet.hpp"
#include "../../GameData/Element.hpp"
#include "../../GameData/Information.hpp"
#include "../../GameData/Command.hpp"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMainWindow>
#include <QKeyEvent>
#include <QRect>
#include <QPolygon>
#include <QPoint>
#include <QLine>
#include <cmath>
#include <QWheelEvent>
#include <iostream>
#include <QRubberBand>
#include "gameview.h"
#include "nm.h"
#include "element.h"
#include "bullet.h"
#include "unit.h"
#include "MyWindow.h"

class GameView;
class Element;
class MyWindow;

class Game
{
public:
    Game(const std::string &, unsigned int , MyWindow *parent = 0);
    ~Game();
    void drawWorld();
    void setPlayerDefinition(const GameData::Information::PlayerDefinition &);
    void setSelection(int unitId);
    void setWorld(GameData::World);
    int angle;
    GameData::World getWorld();
    std::list<Element *> e;
    std::list<GameData::Element> elem;
    std::list<GameData::Unit> unit;
    std::list<GameData::Bullet> bullet;
    std::list<GameData::Physics> pelem;
    std::list<GameData::Physics> punit;
    std::list<GameData::Physics> pbullet;
    GameView *view;
    Nm *n;
    QGraphicsScene *scene;
    MyWindow *win;
    GameData::Information::PlayerDefinition* playerDefinition;
    unsigned int selectedUnit;
private:
    GameData::World world;
};

#endif // GAME_H
