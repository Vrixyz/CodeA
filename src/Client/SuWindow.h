#ifndef SUWINDOW_H
#define SUWINDOW_H

#include "MyWindow.h"

class SuWindow : public QDialog
{
    Q_OBJECT

public:

    SuWindow(int, int, MyWindow*);
    ~SuWindow();

    void setSuPage();
    void creatFields4SuPage();

public slots:

    void checkSu();
    void RecvInfosClient();

private:
    MyWindow*           _parent;

    QPushButton*        _su;
    QPushButton*        _back;
    QPushButton*        _SuQuit;

    QLineEdit*          _loginSuEdit;
    QLineEdit*          _passw1SuEdit;
    QLineEdit*          _passw2SuEdit;
    QLineEdit*          _mailEdit;

    QLabel*             _loginSuLabel;
    QLabel*             _passw1SuLabel;
    QLabel*             _passw2SuLabel;
    QLabel*             _mailLabel;

};

#endif // SUWINDOW_H
