#include "ClassWindow.h"

ClassWindow::ClassWindow(int size_x, int size_y, MyWindow *parent) : QDialog(parent, 0)
{
    _parent = parent;
    setFixedSize(size_x, size_y);
}

ClassWindow::~ClassWindow()
{
}
