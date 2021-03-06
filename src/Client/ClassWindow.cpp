#include "ClassWindow.h"

ClassWindow::ClassWindow(int size_x, int size_y, MyWindow *parent) : QDialog(parent, Qt::FramelessWindowHint)
{
    _parent = parent;
    setFixedSize(size_x, size_y);

    this->move(600, 250);

    setObjectName("classwin");
    setStyleSheet("#classwin { background-image: url(img/classwindow.png); }");

    buildButtons();
}

ClassWindow::~ClassWindow()
{
}

void    ClassWindow::buildButtons()
{
    _class1 = new QPushButton("", this);
    _class2 = new QPushButton("", this);

    _back = new QPushButton("", this);
    _back->setFont(QFont("", 12, 0));
    _back->setStyleSheet("QWidget { background-image: url(img/backto.png); border: 0px; }");

    _class1->setGeometry(35, 50, 160, 180);
    _class2->setGeometry(205, 50, 160, 180);
    _class1->setStyleSheet("QWidget { background-image: url(img/invo_but.png); border: 0px; }");
    _class2->setStyleSheet("QWidget { background-image: url(img/mage_bu.png); border: 0px; }");
    _back->setGeometry(115, 270, 170, 80);

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
    _parent->getDataNet()->setClass("class1");
    _parent->startGame();
}

void    ClassWindow::choiceClass2()
{
    std::cout << "Class2 choisie" << std::endl;
    _parent->getDataNet()->setClass("class2");
    _parent->startGame();
}
