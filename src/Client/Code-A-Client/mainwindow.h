#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <phonon/MediaSource>
#include <phonon/MediaObject>
#include <QCoreApplication>
#include <QTcpSocket>
#include "nm.h"

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
    
private slots:
    void on_pushButton_clicked();
    void Playagain();

private:
    Ui::MainWindow *ui;
    Phonon::MediaObject *music;
};

#endif // MAINWINDOW_H
