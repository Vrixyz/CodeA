#include "GamesWindow.h"
#include "Define.h"

GamesWindow::GamesWindow(int size_x, int size_y, MyWindow *parent) : QDialog(parent, 0/*Qt::FramelessWindowHint*/)
{
    msgpack::sbuffer sbuf;
    msgpack::packer<msgpack::sbuffer> packet(&sbuf);

    _parent = parent;
    setFixedSize(size_x, size_y);

    setStyleSheet("QWidget { background-image: url(img/mainwindow.png); }");

    setTabAndAll();

    packet.pack((int)MasterData::Command::ASK_SERVER_LIST);

    _parent->getDataNet()->getNetwork()->sendToServer(sbuf);

    QObject::connect(_parent->getDataNet()->getNetwork()->getSock(), SIGNAL(readyRead()), this, SLOT(RecvList()));
    QObject::connect(_list, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(tryToCoGame()));
}

GamesWindow::~GamesWindow()
{
}

void    GamesWindow::setTabAndAll()
{
    _tab = new QTabWidget(this);

    _tab->setGeometry(50, 100, 425, 400);
    createTabNews();
    createTabServers();
    createTabSucces();

    _list = new QListWidget(_serversPage);
    _list->setGeometry(10, 40, 380, 280);
    _list->setAttribute(Qt::WA_TranslucentBackground);

    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::white);
    _list->setAutoFillBackground(true);
    _list->setPalette(Pal);
}

void    GamesWindow::createTabNews()
{
    _newsPage = new QWidget(_tab);
    _newsPage->setStyleSheet("QWidget { background-image: url(img/bg-accwin.png); }");
    _tab->addTab(_newsPage, "News");
}

void    GamesWindow::createTabServers()
{
    _serversPage = new QWidget(_tab);
    _tab->addTab(_serversPage, "Servers");
}

void    GamesWindow::createTabSucces()
{
    _succesPage = new QWidget(_tab);
    _tab->addTab(_succesPage, "News");
}

void    GamesWindow::tryToCoGame()
{
    int                                 nbGame;
    std::string                         toSend;
    std::string                         toPars;
    QList<QListWidgetItem *>            tmpList;
    QList<QListWidgetItem *>::Iterator  tmp;

    tmpList = _list->selectedItems();
    tmp = tmpList.begin();
    toPars = (*tmp)->text().toUtf8().constData();
    toSend = "";
    for (unsigned int i = 0; i < toPars.size() && (toPars[i] <= '9' && toPars[i] >= '0'); i++)
        toSend += toPars[i];
    nbGame = stringToInt(toSend);
    std::cout << "TRY DE CONNEXION A LA GAME ---> " << nbGame << std::endl;
}

void    GamesWindow::RecvList()
{
    QByteArray res;
    msgpack::unpacked result;
    msgpack::unpacker pac;

    res = _parent->getDataNet()->getNetwork()->ReceiveFromServer();
    std::cout << "LIST SIZE " << res.length() << std::endl;

    pac.reserve_buffer(res.length());
    memcpy(pac.buffer(), res.data(), res.length());
    pac.buffer_consumed(res.length());
    if (pac.next(&result))
    {
        int idData;
        result.get().convert(&idData);
        if (idData == MasterData::Command::SEND_SERVER_LIST)
        {
            MasterData::Serv serv(0, "");
            while (pac.next(&result))
            {
                result.get().convert(&serv);
                addToList(serv.id, serv.name);
                std::cout << "ID " << serv.id << " NAME " << serv.name << std::endl;
            }
            _parent->getDataNet()->getNetwork()->getSock()->disconnect();
            _list->show();
        }
        else if (idData == MasterData::Command::ERROR)
        {
            MasterData::ErrorMsg err("");
            pac.next(&result);
            result.get().convert(&err);
            std::cerr << "Erreur connexion : " << err.msg << std::endl;
        }
    }

}

void    GamesWindow::addToList(int id, std::string name)
{
    std::string         labelName;
    QListWidgetItem*    item;

    labelName = "";
    labelName += intToString(id);
    labelName += " | ";
    labelName += name;
    QString toto(labelName.c_str());
    item = new QListWidgetItem(toto);
    _list->addItem(item);
}
