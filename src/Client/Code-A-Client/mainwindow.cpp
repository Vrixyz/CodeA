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
    view = new GameView(ui->Main);
//    ui->Gameview->hide();
    // music = Phonon::createPlayer(Phonon::MusicCategory,
    //                              Phonon::MediaSource("/home/edouard/proj_temp/CodeA/src/Client/Code-A-Client/Menu.mp3"));
    // music->play();
    // connect(music, SIGNAL(aboutToFinish()), this, SLOT(Playagain()));
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
    bool sendable = false;
    if (ingame && !(e->isAutoRepeat())) {
        int stat;
        msgpack::sbuffer sbuf;
        msgpack::packer<msgpack::sbuffer> packet(&sbuf);
        switch (e->key()) {
        case Qt::Key_unknown:
            std::cout << "PATRON ELLE PIQUE PAS TA VITEL !" << std::endl;
            break;
        case Qt::Key_B:
            std::cout << "BULLET !" << std::endl;
            sendable = true;
            stat = 0;
            break;
        case Qt::Key_R:
            std::cout << "shield !" << std::endl;
            sendable = true;
            stat = 7;
            break;
        case Qt::Key_Z:
            std::cout << "UP !" << std::endl;
            sendable = true;
            dvectory += 1;
            stat = 3;
            break;
        case Qt::Key_Q:
            std::cout << "LEFT !" << std::endl;
            sendable = true;
            dvectorx -= 1;
            stat = 3;
            break;
        case Qt::Key_S:
            std::cout << "DOWN !" << std::endl;
            sendable = true;
            dvectory -= 1;
            stat = 3;
            break;
        case Qt::Key_D:
            std::cout << "RIGHT !" << std::endl;
            sendable = true;
            dvectorx += 1;
            stat = 3;
            break;
        default:
            std::cout << "Left = " << Qt::Key_Left << ", Right = " << Qt::Key_Right << ", Value = " << e->key() << std::endl;
            break;
        }
        std::cout << "press => vector : (" << dvectorx << ", " << dvectory << ")" << std::endl;
        if (sendable)
        {
            packet.pack(stat);
            packet.pack(dvectorx);
            packet.pack(dvectory);
            n->sendToServer(sbuf);
        }
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *e) {
    bool sendable = false;
    if (ingame && !(e->isAutoRepeat())) {
        int stat;
        msgpack::sbuffer sbuf;
        msgpack::packer<msgpack::sbuffer> packet(&sbuf);
        switch (e->key()) {
        case Qt::Key_unknown:
            std::cout << "PATRON ELLE PIQUE PAS TA VITEL !" << std::endl;
            break;
        case Qt::Key_Z:
            std::cout << "UP !" << std::endl;
            sendable = true;
            stat = 3;
            dvectory -= 1;
            break;
        case Qt::Key_Q:
            std::cout << "LEFT !" << std::endl;
            sendable = true;
            stat = 3;
            dvectorx += 1;
            break;
        case Qt::Key_S:
            std::cout << "DOWN !" << std::endl;
            sendable = true;
            stat = 3;
            dvectory += 1;
            break;
        case Qt::Key_D:
            std::cout << "RIGHT !" << std::endl;
            sendable = true;
            stat = 3;
            dvectorx -= 1;
            break;
        default:
            std::cout << "Left = " << Qt::Key_Left << ", Right = " << Qt::Key_Right << ", Value = " << e->key() << std::endl;
            break;
        }
        std::cout << "release => vector : (" << dvectorx << ", " << dvectory << ")" << std::endl;
        if (sendable)
        {
            packet.pack(stat);
            packet.pack(dvectorx);
            packet.pack(dvectory);
            n->sendToServer(sbuf);
        }
    }
}
