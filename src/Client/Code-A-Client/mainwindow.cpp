#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "nm.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

void MainWindow::NewGame()
{
    music->stop();
    std::cout << "You just started a new game" << std::endl;
    Nm *n = new Nm("127.0.0.1", 4242);
    n->connectToServer();
    QGraphicsItem *item;
    QGraphicsScene *scene = new QGraphicsScene(1600, 900, 0, 0, this);
    QPixmap grass("/home/edouard/proj_temp/CodeA/src/Client/Code-A-Client/grass.png");
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            item = scene->addPixmap(grass);
            item->setPos(i * 100, j * 100);
        }
    }
    QGraphicsView *vue = new QGraphicsView(scene);
    this->setCentralWidget(vue);
    vue->show();
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
