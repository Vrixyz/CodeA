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
    // std::cout << "status courrant " << status << " futur status : " << stat << " angle relatif : " << a << " real angle " << cangle << std::endl;
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
