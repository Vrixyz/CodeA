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

    // Sending information "I want to be a player"
    msgpack::sbuffer sbuf;
    msgpack::packer<msgpack::sbuffer> packet(&sbuf);

    packet.pack((int)GameData::Command::BePlayer);
    n->sendToServer(sbuf);
    //

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
    if (ingame && !(e->isAutoRepeat())) {
        msgpack::sbuffer sbuf;
        msgpack::packer<msgpack::sbuffer> packet(&sbuf);
        switch (e->key()) {
        case Qt::Key_unknown:
            std::cout << "PATRON ELLE PIQUE PAS TA VITEL !" << std::endl;
            break;
        case Qt::Key_B:
            std::cout << "BULLET !" << std::endl;
            packet.pack((int)GameData::Command::Fire);
            packet.pack(GameData::CommandStruct::Fire());
            n->sendToServer(sbuf);
            break;
        case Qt::Key_R:
            std::cout << "shield !" << std::endl;
            packet.pack((int)GameData::Command::Shield);
            packet.pack(GameData::CommandStruct::Shield());
            n->sendToServer(sbuf);
            break;
        case Qt::Key_W:
            setMove(0, 1);
            std::cout << "UP !" << std::endl;
            break;
        case Qt::Key_A:
            std::cout << "LEFT !" << std::endl;
            setMove(-1, 0);
            break;
        case Qt::Key_S:
            std::cout << "DOWN !" << std::endl;
            setMove(0, -1);
            break;
        case Qt::Key_D:
            std::cout << "RIGHT !" << std::endl;
            setMove(1, 0);
            break;
        default:
            std::cout << "Left = " << Qt::Key_Left << ", Right = " << Qt::Key_Right << ", Value = " << e->key() << std::endl;
            break;
        }
        std::cout << "press => vector : (" << dvectorx << ", " << dvectory << ")" << std::endl;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *e) {
    if (ingame && !(e->isAutoRepeat())) {
        switch (e->key()) {
        case Qt::Key_unknown:
            std::cout << "PATRON ELLE PIQUE PAS TA VITEL !" << std::endl;
            break;
        case Qt::Key_W:
            setMove(0, -1);
            std::cout << "UP !" << std::endl;
            break;
        case Qt::Key_A:
            std::cout << "LEFT !" << std::endl;
            setMove(1, 0);
            break;
        case Qt::Key_S:
            std::cout << "DOWN !" << std::endl;
            setMove(0, 1);
            break;
        case Qt::Key_D:
            std::cout << "RIGHT !" << std::endl;
            setMove(-1, 0);
            break;
        default:
            std::cout << "Left = " << Qt::Key_Left << ", Right = " << Qt::Key_Right << ", Value = " << e->key() << std::endl;
            break;
        }
        std::cout << "release => vector : (" << dvectorx << ", " << dvectory << ")" << std::endl;
    }
}

void MainWindow::setMove(int x, int y)
{
    msgpack::sbuffer sbuf;
    msgpack::packer<msgpack::sbuffer> packet(&sbuf);
    GameData::CommandStruct::Move m;
    dvectorx += x;
    dvectory += y;
    packet.pack((int)GameData::Command::Move);
    m.x = dvectorx;
    m.y = dvectory;
    m.idUnit = 0;
    packet.pack(m);
    n->sendToServer(sbuf);
}
