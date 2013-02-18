#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QApplication>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QList>
#include <QFont>

#include <QListWidgetItem>
#include <QListWidget>
#include <QHBoxLayout>
#include <QWidget>

#include <iostream>
#include <list>

struct s_game
{
    int id;
    int size;
    std::string name;
} typedef t_game;

class MyWindow : public QWidget
{
    Q_OBJECT

public:
    MyWindow(int, int);
    void createQuit(int, int, int, int);
    void createCo(int, int, int, int);
    void creatFields();

    void cleanAndShow();
    void showGames();
    void initGames();

public slots:
    void checkCo();
    void tryCoToGame();

private:
    std::list<t_game> allGames;

    QListWidget *list;

    QPushButton *quit;
    QPushButton *aquit;
    QPushButton *co;
    QLineEdit* loginEdit;
    QLineEdit* passwEdit;
    QLabel* loginLabel;
    QLabel* passwLabel;
};

std::string intToString(int);
int stringToInt(std::string);

#endif // MYWINDOW_H
