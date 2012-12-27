#ifndef GAME_H
#define GAME_H

#include "../../GameData/World.hpp"
#include "../../GameData/Physics.hpp"
#include "../../GameData/Unit.hpp"
#include "../../GameData/Bullet.hpp"
#include "../../GameData/Element.hpp"
#include "../../GameData/Information.hpp"
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
    void setPlayerDefinition(const GameData::Information::PlayerDefinition &);
    void setSelection(int unitId);
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

    GameData::Information::PlayerDefinition* playerDefinition;
    unsigned int selectedUnit;
private:
    GameData::World world;
};

#endif // GAME_H
