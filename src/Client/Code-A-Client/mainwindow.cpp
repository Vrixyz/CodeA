#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "nm.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    dvectorx = 0;
    dvectory = 0;
    ui->setupUi(this);
    this->setFocusProxy(view);
    ingame = false;
    NewGame();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Playagain()
{
    // music->enqueue(Phonon::MediaSource("/home/edouard/proj_temp/CodeA/src/Client/Code-A-Client/Menu.mp3"));
    // music->play();
}


void MainWindow::NewGame()
{
    ingame = true;
    //    music->stop();
    std::cout << "You just started a new game" << std::endl;
    game = new Game(this, view);
    n = new Nm("127.0.0.1", 4242, game);
    view->bindNet(n);
    n->connectToServer();
    ui->Loginpage->hide();
    // Sending information "I want to be a player"
    msgpack::sbuffer sbuf;
    msgpack::packer<msgpack::sbuffer> packet(&sbuf);
    packet.pack((int)GameData::Command::BePlayer);
    n->sendToServer(sbuf);
}

void MainWindow::on_loginb_pressed()
{
    std::cout << ui->logini->displayText().toStdString() << " " << ui->passwordi->text().toStdString() << std::endl;
    if (ui->logini->text() == "root" && ui->passwordi->text() == "toor")
    {
        std::cout << "login ok !" << std::endl;
        NewGame();
    }
    else
        std::cout << "login ko !" << std::endl;
}
