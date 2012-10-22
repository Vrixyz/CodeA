#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "nm.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) , game(new Game(this))
{
    ui->setupUi(this);
    ui->Gameview->hide();
    music = Phonon::createPlayer(Phonon::MusicCategory,
                                 Phonon::MediaSource("/home/edouard/proj_temp/CodeA/src/Client/Code-A-Client/Menu.mp3"));
    music->play();
    connect(music, SIGNAL(aboutToFinish()), this, SLOT(Playagain()));
    ingame = false;
    NewGame();
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

void MainWindow::NewGame()
{
    ingame = true;
    music->stop();
    std::cout << "You just started a new game" << std::endl;
    n = new Nm("127.0.0.1", 4242, game);
    n->connectToServer();
    ui->Loginpage->hide();
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

void MainWindow::keyPressEvent(QKeyEvent *e) {

    if (ingame) {
        GameData::Command cmd;
        msgpack::sbuffer sbuf;
        msgpack::packer<msgpack::sbuffer> packet(&sbuf);
        switch (e->key()) {
        case Qt::Key_unknown:
            std::cout << "PATRON ELLE PIQUE PAS TA VITEL !" << std::endl;
            break;
        case Qt::Key_W:
            std::cout << "UP !" << std::endl;
            cmd.type = 3;
            cmd.y = 1;
            packet.pack(cmd);
            n->sendToServer(sbuf);
            break;
        case Qt::Key_A:
            std::cout << "LEFT !" << std::endl;
            cmd.type = 3;
            cmd.x = -1;
            packet.pack(cmd);
            n->sendToServer(sbuf);
            break;
        case Qt::Key_S:
            std::cout << "DOWN !" << std::endl;
            cmd.type = 3;
            cmd.y = -1;
            packet.pack(cmd);
            n->sendToServer(sbuf);
            break;
        case Qt::Key_D:
            std::cout << "RIGHT !" << std::endl;
            cmd.type = 3;
            cmd.x = 1;
            packet.pack(cmd);
            n->sendToServer(sbuf);
            break;
        case Qt::Key_Up:
            std::cout << "UP !" << std::endl;
            cmd.type = 3;
            cmd.y = 1;
            packet.pack(cmd);
            n->sendToServer(sbuf);
            break;
        case Qt::Key_Left:
            std::cout << "LEFT !" << std::endl;
            cmd.type = 3;
            cmd.x = -1;
            packet.pack(cmd);
            n->sendToServer(sbuf);
            break;
        case Qt::Key_Down:
            std::cout << "DOWN !" << std::endl;
            cmd.type = 3;
            cmd.y = -1;
            packet.pack(cmd);
            n->sendToServer(sbuf);
            break;
        case Qt::Key_Right:
            std::cout << "RIGHT !" << std::endl;
            cmd.type = 3;
            cmd.x = 1;
            packet.pack(cmd);
            n->sendToServer(sbuf);
            break;
        default:
            std::cout << "Left = " << Qt::Key_Left << ", Right = " << Qt::Key_Right << ", Value = " << e->key() << std::endl;
            break;
        }
    }
}
