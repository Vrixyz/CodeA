#include "gameview.h"

GameView::GameView(QWidget *parent) : QGraphicsView(parent)
{
    status = 6;
    dvectorx = 0;
    dvectory = 0;
    cangle = 0;
    setObjectName(QString::fromUtf8("Gameview"));
    setGeometry(QRect(0, 0, 800, 600));
    setMouseTracking(true);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setInteractive(true);
    setSceneRect(QRectF(-400, -300, 800, 600));
}

void GameView::mouseMoveEvent(QMouseEvent *e)
{
    int stat;
    msgpack::sbuffer sbuf;
    msgpack::packer<msgpack::sbuffer> packet(&sbuf);
    double fa;
    int a;
    QPoint p;
    e->pos();
    p = e->pos();
    p.setX(p.x() - 400);
    p.setY(-(p.y() - 300));
    if ((p.y() * p.x()) > 0)
        fa = std::fabs(abs(p.x()) / std::fabs(p.y()));
    else
        fa = std::fabs(abs(p.y()) / std::fabs(p.x()));
    a = std::atan(fa) * 180 / (4.0 * std::atan(1.0));
    if (p.x() >= 0 && p.y() <= 0)
        a += 90;
    else if (p.x() <= 0 && p.y() < 0)
        a += 180;
    else if (p.x() <= 0 && p.y() >= 0)
        a += 270;
    cangle = a;
    a -= angle;
    if (a <= 0)
        a = 360 + a;
    if (a < 350 && a > 180)
        stat = 4;
    else if (a > 10 && a <= 180)
        stat = 5;
    else
        stat = 6;
    if (stat != status)
    {
        GameData::CommandStruct::Rotate r;
        r.idUnit = n->game->selectedUnit;
        std::cout << "id: " << r.idUnit << std::endl;
        packet.pack(stat);
        packet.pack(r);
        n->sendToServer(sbuf);
        status = stat;
        if (status == 4)
            std::cout << "Go Left !" << std::endl;
        else if (status == 5)
            std::cout << "Go Right !" << std::endl;
        else
            std::cout << "Keep Going !" << std::endl;
    }
}

void GameView::bindNet(Nm *s)
{
    n = s;
}

void GameView::rotationUpdate()
{
    msgpack::sbuffer sbuf;
    msgpack::packer<msgpack::sbuffer> packet(&sbuf);
    int stat;
    int a = cangle;
    a -= angle;
    if (a <= 0)
        a = 360 + a;
    if (a < 350 && a > 180)
        stat = 4;
    else if (a > 10 && a <= 180)
        stat = 5;
    else
        stat = 6;
    if (stat != status)
    {
        GameData::CommandStruct::Rotate r;
        r.idUnit = n->game->selectedUnit;
        packet.pack(stat);
        packet.pack(r);
        n->sendToServer(sbuf);
        status = stat;
        if (status == 4)
            std::cout << "Go Left ! (up)" << std::endl;
        else if (status == 5)
            std::cout << "Go Right ! (up)" << std::endl;
        else
            std::cout << "Keep Going ! (up)" << std::endl;
    }
}

void GameView::mousePressEvent(QMouseEvent *event)
{
    msgpack::sbuffer sbuf;
    msgpack::packer<msgpack::sbuffer> packet(&sbuf);
    switch (event->button())
    {
    case Qt::LeftButton:
        packet.pack((int)GameData::Command::Fire);
        GameData::CommandStruct::Fire f;
        f.x = 0;
        f.y = 0;
        f.idUnit = n->game->selectedUnit;
        packet.pack(f);
        n->sendToServer(sbuf);
        break;

    default:
        std::cout << "nothing" << std::endl;
        break;
    }
}

void GameView::wheelEvent(QWheelEvent *e)
{
    int delta = e->delta();
    this->geometry();
    if (delta < 0)
        this->scale(0.9, 0.9);
    else
        this->scale(1.1, 1.1);
}

void GameView::keyPressEvent(QKeyEvent *e) {
    if (!(e->isAutoRepeat())) {
        msgpack::sbuffer sbuf;
        msgpack::packer<msgpack::sbuffer> packet(&sbuf);
        switch (e->key()) {
        case Qt::Key_unknown:
            std::cout << "PATRON ELLE PIQUE PAS TA VITEL !" << std::endl;
            break;
        case Qt::Key_B:
            GameData::CommandStruct::Fire f;
            f.idUnit = n->game->selectedUnit;
            std::cout << "BULLET !" << std::endl;
            packet.pack((int)GameData::Command::Fire);
            packet.pack(f);
            n->sendToServer(sbuf);
            break;
        case Qt::Key_R:
            GameData::CommandStruct::Shield s;
            s.idUnit = n->game->selectedUnit;
            std::cout << "shield !" << std::endl;
            packet.pack((int)GameData::Command::Shield);
            packet.pack(s);
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

void GameView::keyReleaseEvent(QKeyEvent *e) {
    if (!(e->isAutoRepeat())) {
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

void  GameView::setMove(int x, int y)
{
    msgpack::sbuffer sbuf;
    msgpack::packer<msgpack::sbuffer> packet(&sbuf);
    GameData::CommandStruct::Move m;
    dvectorx += x;
    dvectory += y;
    packet.pack((int)GameData::Command::Move);
    m.x = dvectorx;
    m.y = dvectory;
    m.idUnit = n->game->selectedUnit;
    std::cout << "unit id : " << m.idUnit << std::endl;
    packet.pack(m);
    n->sendToServer(sbuf);
}
