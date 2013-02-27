#include "MyWindow.h"

#include "SuWindow.h"
#include "AccWindow.h"
#include "ClassWindow.h"
#include "GamesWindow.h"

MyWindow::MyWindow(int size_x, int size_y) : QWidget()
{
    _dataNet = new Store();
    setFixedSize(size_x, size_y);
    _suWindow = NULL;
    _accWindow = NULL;
    _gamesWindow = NULL;
    _classWindow = NULL;
}

MyWindow::~MyWindow()
{
}

void    MyWindow::startGame(int port, std::string ip)
{
    _gamesWindow->hide();
    show();
}

void    MyWindow::endGame()
{
    hide();
    _gamesWindow->show();
}

void    MyWindow::setGamesWindow()
{
    _gamesWindow = new GamesWindow(1000, 500, this);
    _gamesWindow->show();
    if ((_accWindow != NULL) && _accWindow->isActiveWindow() == 1)
        _accWindow->hide();
    if ((_classWindow != NULL) && _classWindow->isActiveWindow() == 1)
        _classWindow->hide();
}

void    MyWindow::setSuWindow()
{
    _suWindow = new SuWindow(400, 400, this);
    _suWindow->show();
    _accWindow->hide();
}

void    MyWindow::setAccWindow()
{
    if (_accWindow == NULL)
        _accWindow = new AccWindow(400, 400, this);
    _accWindow->show();
    if ((_suWindow != NULL) && _suWindow->isActiveWindow() == 1)
        _suWindow->hide();
}

void    MyWindow::setClassWindow()
{
    if (_classWindow == NULL)
        _classWindow = new ClassWindow(400, 400, this);
    _classWindow->show();
    if ((_gamesWindow != NULL) && _gamesWindow->isActiveWindow() == 1)
        _gamesWindow->hide();
}

QDialog *MyWindow::getGamesWindow(void)
{
    return _gamesWindow;
}

QDialog *MyWindow::getSuWindow(void)
{
    return _suWindow;
}

QDialog *MyWindow::getAccWindow(void)
{
    return _accWindow;
}

void    MyWindow::setDataNet(Store *dataNet)
{
    _dataNet = dataNet;
}

Store*  MyWindow::getDataNet()
{
    return _dataNet;
}

void    MyWindow::setPort(int p)
{
    _port = p;
}

int     MyWindow::getPort(void)
{
    return _port;
}
