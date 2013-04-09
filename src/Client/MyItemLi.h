#ifndef MYITEM_H
#define MYITEM_H

#include "game.h"
#include <QtGui>


class MyItemLi : public QListWidgetItem
{
//    Q_OBJECT

public:

    MyItemLi(int);
    ~MyItemLi();
    void setId(int);
    int getId(void);

private:

    int _id;

};

#endif // MYITEM_H
