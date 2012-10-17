#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
// #include <phonon/MediaSource>
// #include <phonon/MediaObject>
#include <QCoreApplication>
#include <QTcpSocket>
#include <QPixmap>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <list>
#include "nm.h"
#include "game.h"

class Nm;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    void NewGame();
    ~MainWindow();
    Ui::MainWindow *ui;
    
private slots:
    void Playagain();
    void on_loginb_pressed();

private:
//    Phonon::MediaObject *music;
    Nm *n;
    Game *game;
};

#endif // MAINWINDOW_H


