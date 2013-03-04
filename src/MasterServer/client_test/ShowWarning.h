#ifndef SHOWWARNING_H
#define SHOWWARNING_H

#include "MyWindow.h"

#include <QtGui>

class ShowWarning : public QMessageBox
{

    Q_OBJECT

public:

    ShowWarning(MyWindow *, std::string);
    ~ShowWarning();

    void setMsg(std::string);
    std::string getMsg(void);

private:

    MyWindow*       _parent;
    std::string    _msg;

};

#endif // SHOWWARNING_H
