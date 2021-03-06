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
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setInteractive(true);
    setSceneRect(QRectF(-400, -300, 800, 600));
    rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
    this->setFocus();
}

void GameView::mouseMoveEvent(QMouseEvent *e)
{
    rubberBand->setGeometry(QRect(base, e->pos()).normalized());
    if (this->n->game->isRTS == false)
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
    else
    {
        mouse = e->pos();
        viewMove();
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
    if (n->game->isRTS)
    {
        switch (event->button())
        {
        case Qt::LeftButton:
            base = event->pos();
            rubberBand->setGeometry(QRect(base, QSize()));
            rubberBand->show();
            break;

        case Qt::RightButton:
        {
            GameData::CommandStruct::MoveTo m;
            m.idUnits = n->game->idList;
            m.x = event->pos().x() + sceneRect().x();
            m.y = -(event->pos().y() + sceneRect().y());
            packet.pack((int)GameData::Command::MoveTo);
            packet.pack(m);
            n->sendToServer(sbuf);
            std::cout << "send moveTo " << m.x << " " << m.y << std::endl;
            sbuf.clear();
            break;
        }

        default:
            std::cout << "nothing" << std::endl;
            break;
        }
    }
}

void GameView::mouseReleaseEvent(QMouseEvent *event)
{
    if (n->game->isRTS)
    {
        switch (event->button())
        {
        case Qt::LeftButton:
        {
            n->game->idList.clear();
            QGraphicsItem *item;
            QRectF *rect = new QRectF(rubberBand->geometry().x() + sceneRect().x(), rubberBand->geometry().y() + sceneRect().y(), rubberBand->width(), rubberBand->height());
            std::cout << "Rectangle de selection " << rect->x() << " " << rect->y() << std::endl;
            rubberBand->hide();
            QList<QGraphicsItem *> list = this->n->game->scene->items(*rect);
            std::cout << "Il se passe quelque chose ! " << list.size() << std::endl;
            for (int i = 0; i < list.length(); i++)
            {
                item = list.at(i);
                std::cout << "item pos => x : " << item->x() << " y : " << item->y() << std::endl;
                switch (list.at(i)->type())
                {
                case Bullet::Type:
                    Bullet *bullet;
                    bullet = static_cast<Bullet *>(item);
                    n->game->idList.push_back(bullet->bullet.id);
                    std::cout << "Bullet" << std::endl;
                    break;

                case Element::Type:
                    Element *element;
                    element = static_cast<Element *>(item);
                    n->game->idList.push_back(element->elem.id);
                    std::cout << "Element" << std::endl;
                    break;

                case Unit::Type:
                    Unit *unit;
                    unit = static_cast<Unit *>(item);
                    n->game->idList.push_back(unit->unit.id);
                    std::cout << "Unit" << std::endl;
                    break;

                default:
                    std::cout << "whatever" << std::endl;
                    break;
                }
            }
            break;
        }

        default:
            break;
        }
    }
}

void GameView::wheelEvent(QWheelEvent *e)
{
    int delta = e->delta();
    if (delta < 0)
        this->scale(0.9, 0.9);
    else
        this->scale(1.1, 1.1);
}

void GameView::keyPressEvent(QKeyEvent *e) {
    if (!(e->isAutoRepeat()) && !(n->game->isRTS)) {
        msgpack::sbuffer sbuf;
        msgpack::packer<msgpack::sbuffer> packet(&sbuf);
        switch (e->key()) {
        case Qt::Key_unknown:
            std::cout << "PATRON ELLE PIQUE PAS TA VITEL !" << std::endl;
            break;
        case Qt::Key_B:
            GameData::CommandStruct::Fire f;
            f.idUnit = n->game->selectedUnit;
            packet.pack((int)GameData::Command::Fire);
            packet.pack(f);
            n->sendToServer(sbuf);
            break;
        case Qt::Key_R:
            GameData::CommandStruct::Shield s;
            s.idUnit = n->game->selectedUnit;
            packet.pack((int)GameData::Command::Shield);
            packet.pack(s);
            n->sendToServer(sbuf);
            break;
        case Qt::Key_W:
            setMove(0, 1);
            break;
        case Qt::Key_A:
            setMove(-1, 0);
            break;
        case Qt::Key_S:
            setMove(0, -1);
            break;
        case Qt::Key_D:
            setMove(1, 0);
            break;
        case Qt::Key_Escape:
            delete this->n->game;
            break;
        default:
            break;
        }
        std::cout << "press => vector : (" << dvectorx << ", " << dvectory << ")" << std::endl;
    }
    else if (!(e->isAutoRepeat()))
    {
        switch (e->key()) {
        case Qt::Key_Escape:
            this->n->game->win->endGame();
            break;
        }
    }
}

void GameView::keyReleaseEvent(QKeyEvent *e) {
    if (!(e->isAutoRepeat()) && !(n->game->isRTS)) {
        switch (e->key()) {
        case Qt::Key_unknown:
            std::cout << "PATRON ELLE PIQUE PAS TA VITEL !" << std::endl;
            break;
        case Qt::Key_W:
            setMove(0, -1);
            break;
        case Qt::Key_A:
            setMove(1, 0);
            break;
        case Qt::Key_S:
            setMove(0, 1);
            break;
        case Qt::Key_D:
            setMove(-1, 0);
            break;
        default:
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
    packet.pack(m);
    n->sendToServer(sbuf);
}

void GameView::viewMove()
{
    int xlcoef = mouse.x();
    int xrcoef = mouse.x();
    int yucoef = mouse.y();
    int ydcoef = mouse.y();
    xlcoef = (int)(round(1. / (xlcoef / (this->width() * 0.1)))) % 10;
    yucoef = (int)(round(1. / (yucoef / (this->height() * 0.1)))) % 10;
    xrcoef = (int)(round(1. / ((this->width() * 0.1) / xrcoef * 0.1))) % 10;
    ydcoef = (int)(round(1. / ((this->height() * 0.1) / ydcoef * 0.1))) % 10;
//    std::cout << "coeff x : " << xlcoef << " " << xrcoef << " coeff y : " << yucoef << " " << ydcoef << std::endl;
    if (mouse.x() < (this->width() * 0.1))
        this->setSceneRect(this->sceneRect().x() - xlcoef, this->sceneRect().y(), this->width(), this->height());
    if (mouse.x() > (this->width() * 0.9))
        this->setSceneRect(this->sceneRect().x() + xrcoef, this->sceneRect().y(), this->width(), this->height());
    if (mouse.y() > (this->height() * 0.9))
        this->setSceneRect(this->sceneRect().x(), this->sceneRect().y() + ydcoef, this->width(), this->height());
    if (mouse.y() < (this->height() * 0.1))
        this->setSceneRect(this->sceneRect().x(), this->sceneRect().y() - yucoef, this->width(), this->height());
}
