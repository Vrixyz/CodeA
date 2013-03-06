#ifndef CLASSWINDOW_H
#define CLASSWINDOW_H

#include "MyWindow.h"

class ClassWindow : public QDialog
{
    Q_OBJECT

public:

    ClassWindow(int, int, MyWindow*);
    ~ClassWindow();

    void buildButtons();

public slots:

    void choiceClass1();
    void choiceClass2();

private:

    QPushButton*    _class1;
    QPushButton*    _class2;
    QPushButton*    _back;

    MyWindow*       _parent;

};

#endif // CLASSWINDOW_H
