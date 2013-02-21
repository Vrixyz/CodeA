#ifndef CLASSWINDOW_H
#define CLASSWINDOW_H

#include "MyWindow.h"

class ClassWindow : public QDialog
{
    Q_OBJECT

public:

    ClassWindow(int, int, MyWindow*);
    ~ClassWindow();

public slots:

private:

    MyWindow*           _parent;

};

#endif // CLASSWINDOW_H
