#ifndef GAME_H
#define GAME_H

#include "../../GameData/World.hpp"
#include "../../GameData/Physics.hpp"
#include "../../GameData/Unit.hpp"
#include "../../GameData/Bullet.hpp"
#include "../../GameData/Element.hpp"
#include "mainwindow.h"

class MainWindow;
class GameView;
namespace Ui
{
class MainWindow;
}

class Game
{
public:
    Game(MainWindow *, GameView *);
    void drawWorld();
    void setWorld(GameData::World);
    int angle;
    GameData::World getWorld();
    std::list<GameData::Element> elem;
    std::list<GameData::Unit> unit;
    std::list<GameData::Bullet> bullet;
    std::list<GameData::Physics> pelem;
    std::list<GameData::Physics> punit;
    std::list<GameData::Physics> pbullet;
    GameView *view;
    MainWindow *ui;

private:
    GameData::World world;
};

#endif // GAME_H
