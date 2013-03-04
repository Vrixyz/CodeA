#include "GamesWindow.h"
#include "MyItemLi.h"
#include "Define.h"

GamesWindow::GamesWindow(int size_x, int size_y, MyWindow *parent) : QDialog(parent, 0/*Qt::FramelessWindowHint*/)
{
    msgpack::sbuffer sbuf;
    msgpack::packer<msgpack::sbuffer> packet(&sbuf);

    _parent = parent;
    setFixedSize(size_x, size_y);

    setObjectName("gameswindow");
    setStyleSheet("#gameswindow { background-image: url(img/mainwindowall.png); }");

    setTabAndAll();

    packet.pack((int)MasterData::Command::ASK_SERVER_LIST);

    _parent->getDataNet()->getNetwork()->sendToServer(sbuf);

    QObject::connect(_parent->getDataNet()->getNetwork()->getSock(), SIGNAL(readyRead()), this, SLOT(RecvData()));
    QObject::connect(_list, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(tryToCoGame()));
    QObject::connect(_join, SIGNAL(clicked()), this, SLOT(tryToCoGame()));
    QObject::connect(_match, SIGNAL(clicked()), this, SLOT(tryToMatchmaking()));
    QObject::connect(_refresh, SIGNAL(clicked()), this, SLOT(refreshServ()));
}

GamesWindow::~GamesWindow()
{
}

void    GamesWindow::refreshServ()
{
}

void    GamesWindow::setTabAndAll()
{
    _tab = new QTabWidget(this);

    _tab->setGeometry(50, 77, 425, 400);
    _tab->setStyleSheet(" QTabWidget::pane {"
                        " border-top: px solid #000000;"
                        " position: absolute;"
                        " top: -2em;"
                        " }"
                        " QTabWidget::tab-bar {"
                        " alignment: center;"
                        " }");

    createTabServers();
    createTabNews();
    createTabSucces();

    _list = new QListWidget(_serversPage);
    _list->setGeometry(15, 122, 200, 200);

    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::white);
    _list->setAutoFillBackground(true);
    _list->setPalette(Pal);

    _readChat = new QTextEdit("", this);
    _readChat->setAttribute(Qt::WA_TranslucentBackground);
    _readChat->setGeometry(536, 103, 390, 320);
    _readChat->setStyleSheet("QTextEdit { background-image : url(img/bg-chat.png) ; border: 0px; } ");
    _readChat->setReadOnly(1);

    _writeChat = new QLineEdit(this);
    _writeChat->setAttribute(Qt::WA_TranslucentBackground);
    _writeChat->setStyleSheet("QLineEdit { background-image : url(img/bg-chatdial.png) ; border: 0px; } ");
    _writeChat->setGeometry(536, 430, 390, 25);

    QObject::connect(_writeChat, SIGNAL(returnPressed()), this, SLOT(sendMsg()));
}

void    GamesWindow::sendMsg()
{
    msgpack::sbuffer sbuf;
    msgpack::packer<msgpack::sbuffer> packet(&sbuf);

    packet.pack((int)MasterData::Command::SEND_CHAT);
    MasterData::SendChat tosend(_writeChat->text().toUtf8().constData());
    _writeChat->clear();
    packet.pack(tosend);
    _parent->getDataNet()->getNetwork()->sendToServer(sbuf);
}

void    GamesWindow::createTabNews()
{
    _newsPage = new QWidget(_tab);
    _tab->addTab(_newsPage, "        News        ");
}

void    GamesWindow::createTabServers()
{
    _serversPage = new QWidget(_tab);

    _match = new QPushButton("Matchmaking", _serversPage);
    _refresh = new QPushButton("Refresh", _serversPage);
    _join = new QPushButton("Join", _serversPage);

    _match->setGeometry(15, 42, 200, 50);
    _refresh->setGeometry(218, 42, 200, 50);
    _join->setGeometry(15, 335, 200, 50);

    _match->setAutoDefault(0);
    _refresh->setAutoDefault(0);
    _join->setAutoDefault(0);

    _iServ = new QLabel("<font color=\"#e7d593\">Liste des serveurs :</font>", _serversPage);
    _iServ->setGeometry(52, 95, 150, 20);
    _tab->addTab(_serversPage, "       Servers       ");
}

void    GamesWindow::createTabSucces()
{
    _succesPage = new QWidget(_tab);
    _tab->addTab(_succesPage, "      Succes       ");
}

void    GamesWindow::tryToMatchmaking()
{
    std::cout << "TO DO : Implementation du matchmaking." << std::endl;
}

void    GamesWindow::tryToCoGame()
{
    int                                 nbGame;
    std::string                         toSend;
    std::string                         toPars;
    QList<QListWidgetItem *>            tmpList;
    QList<QListWidgetItem *>::Iterator  tmp;

    tmpList =_list->selectedItems();
    if (tmpList.size() == 0)
        return;
    tmp = tmpList.begin();
    toPars = (*tmp)->text().toUtf8().constData();
    toSend = "";
    for (unsigned int i = 0; i < toPars.size() && (toPars[i] <= '9' && toPars[i] >= '0'); i++)
        toSend += toPars[i];
    nbGame = stringToInt(toSend);

    // ON ENVOI AU SERVEUR LE CHOIX DE GAME
    msgpack::sbuffer sbuf;
    msgpack::packer<msgpack::sbuffer> packet(&sbuf);

    packet.pack((int)MasterData::Command::REQUEST_SERVER);
    packet.pack(nbGame);

    _parent->getDataNet()->getNetwork()->sendToServer(sbuf);
}

void    GamesWindow::RecvList(QByteArray res)
{
    msgpack::unpacked result;
    msgpack::unpacker pac;

    pac.reserve_buffer(res.length());
    memcpy(pac.buffer(), res.data(), res.length());
    pac.buffer_consumed(res.length());
    std::cout << "RECEPTION DE LA LIST DE SERV" << std::endl;
    if (pac.next(&result))
    {
        MasterData::Serv serv(0, "");
        _list->clear();
        while (pac.next(&result))
        {
            result.get().convert(&serv);
            addToList(serv.id, serv.name);
            std::cout << "ID " << serv.id << " NAME " << serv.name << std::endl;
        }
        //  PAS DE CO POUR LES PROCHAINES LECTURES
        //      _parent->getDataNet()->getNetwork()->getSock()->disconnect();
        _list->show();
    }
}

void    GamesWindow::RecvError(QByteArray res)
{
    msgpack::unpacked	result;
    msgpack::unpacker	pac;

    pac.reserve_buffer(res.length());
    memcpy(pac.buffer(), res.data(), res.length());
    pac.buffer_consumed(res.length());
    if (pac.next(&result))
    {
        MasterData::ErrorMsg err("");
        pac.next(&result);
        result.get().convert(&err);

        QMessageBox::warning(this, tr("Erreur"), tr(err.msg.c_str()));
    }
}

void    GamesWindow::RecvServer(QByteArray res)
{
    msgpack::unpacked result;
    msgpack::unpacker pac;

    pac.reserve_buffer(res.length());
    memcpy(pac.buffer(), res.data(), res.length());
    pac.buffer_consumed(res.length());
    if (pac.next(&result))
    {
        MasterData::InfosServer serv("", 0);
        pac.next(&result);
        result.get().convert(&serv);
        std::cerr << "INFOS DE CONNEXION IP:" << serv.ip << " PORT:" << serv.port << std::endl;
        //PARSER LA STRUCT D'infos SERVEUR ET FAIRE LE BORDEL QUE DORIAN DOIT FAIRE!

    }
}

void	GamesWindow::RecvChat(QByteArray res)
{
    msgpack::unpacked result;
    msgpack::unpacker pac;

    pac.reserve_buffer(res.length());
    memcpy(pac.buffer(), res.data(), res.length());
    pac.buffer_consumed(res.length());
    if (pac.next(&result))
    {
        MasterData::RecvChat recv("", "");
        pac.next(&result);
        result.get().convert(&recv);
        _readChat->insertPlainText(QString(recv.from.data()) + ": " + QString(recv.msg.data()) + "\n");
    }
}

void    GamesWindow::RecvData()
{
    QByteArray res;
    msgpack::unpacked result;
    msgpack::unpacker pac;

    res = _parent->getDataNet()->getNetwork()->ReceiveFromServer();
    pac.reserve_buffer(res.length());
    memcpy(pac.buffer(), res.data(), res.length());
    pac.buffer_consumed(res.length());
    std::cout << "RECV_DATA" << std::endl;
    if (pac.next(&result))
    {
        int idData;
        result.get().convert(&idData);
        switch(idData)
        {
        case MasterData::Command::SEND_SERVER_LIST:
            RecvList(res);
            break;
        case MasterData::Command::RECV_CHAT:
            RecvChat(res);
            break;
        case MasterData::Command::INFOS_SERVER:
            RecvServer(res);
            break;
        case MasterData::Command::ERROR:
            RecvError(res);
            break;
        default:
            std::cerr << "Command inconnu" << std::endl;
            break;
        };
    }
}

void    GamesWindow::addToList(int id, std::string name)
{
    std::string         labelName;
    MyItemLi*           item;

    labelName = "";
    labelName += intToString(id);
    labelName += " | ";
    labelName += name;
    QString toto(labelName.c_str());
    item = new MyItemLi(id);
    item->setText(toto);
    _list->addItem(item);
}
