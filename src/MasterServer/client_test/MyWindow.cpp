#include "MyWindow.h"
#include "AccWindow.h"

MyWindow::MyWindow(int size_x, int size_y) : QWidget()
{
    _dataNet = new Store();
    setFixedSize(size_x, size_y);
}

MyWindow::~MyWindow()
{
}

void    MyWindow::setCoWindow(int x , int y)
{
    _coWindow = new AccWindow(x, y, this);
    _coWindow->setFixedSize(x, y);
}

QDialog *MyWindow::getCoWindow(void)
{
    return _coWindow;
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
