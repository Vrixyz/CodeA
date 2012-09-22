#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "nm.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_2, SIGNAL(clicked()), qApp, SLOT(quit()));
    music = Phonon::createPlayer(Phonon::MusicCategory,
                                 Phonon::MediaSource("/home/edouard/proj_temp/CodeA/src/Client/Code-A-Client/Menu.mp3"));
    music->play();
    connect(music, SIGNAL(aboutToFinish()), this, SLOT(Playagain()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Playagain()
{
    music->enqueue(Phonon::MediaSource("/home/edouard/proj_temp/CodeA/src/Client/Code-A-Client/Menu.mp3"));
    music->play();
}

void MainWindow::on_pushButton_clicked()
{
    NewGame();
}
void MainWindow::NewGame()
{
    music->stop();
    ui->pushButton->close();
    ui->pushButton_2->close();
    std::cout << "You just started a new game" << std::endl;
    Nm *n = new Nm("127.0.0.1", 4242);
    n->connectToServer();
}
