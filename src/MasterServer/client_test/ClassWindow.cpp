#include "ClassWindow.h"

ClassWindow::ClassWindow(int size_x, int size_y, MyWindow *parent) : QDialog(parent, 0)
{
    _parent = parent;
    setFixedSize(size_x, size_y);

    buildButtons();
}

ClassWindow::~ClassWindow()
{
}

void    ClassWindow::buildButtons()
{
    _class1 = new QPushButton("Class1", this);
    _class2 = new QPushButton("Class2", this);
    _back = new QPushButton("Retour au menu", this);

    _class1->setGeometry(20, 20, 170, 170);
    _class2->setGeometry(210, 20, 170, 170);
    _back->setGeometry(115, 250, 170, 80);

    _class1->setAutoDefault(0);
    _class2->setAutoDefault(0);
    _back->setAutoDefault(0);

     QObject::connect(_class1, SIGNAL(clicked()), this, SLOT(choiceClass1()));
     QObject::connect(_class2, SIGNAL(clicked()), this, SLOT(choiceClass2()));
     QObject::connect(_back, SIGNAL(clicked()), _parent, SLOT(setGamesWindow()));
}

void    ClassWindow::choiceClass1()
{
    std::cout << "Class1 choisie" << std::endl;
}

void    ClassWindow::choiceClass2()
{
    std::cout << "Class2 choisie" << std::endl;
}
