#include "GamesWindow.h"
#include "MyItemLi.h"
#include "Define.h"
#include "Achi.h"

#include <QtWebKit/QWebView>

void	GamesWindow::SendCMD(int cmd)
{
  msgpack::sbuffer sbuf;
  msgpack::packer<msgpack::sbuffer> packet(&sbuf);
  packet.pack(cmd);
  _parent->getDataNet()->getNetwork()->sendToServer(sbuf);
}

GamesWindow::GamesWindow(int size_x, int size_y, MyWindow *parent) : QDialog(parent, 0/*Qt::FramelessWindowHint*/)
{

    _parent = parent;
    setFixedSize(size_x, size_y);

    this->move(300, 200);

    setObjectName("gameswindow");
    setStyleSheet("#gameswindow { background-image: url(img/mainwindowall.png); }");

    setTabAndAll();

    SendCMD((int)MasterData::Command::ASK_SERVER_LIST);

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
  SendCMD((int)MasterData::Command::ASK_SUCCES);
}

void    GamesWindow::setTabAndAll()
{
    _tab = new QTabWidget(this);

    _tab->setGeometry(50, 77, 430, 400);
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
    _writeChat->setGeometry(576, 430, 330, 25);

    QObject::connect(_writeChat, SIGNAL(returnPressed()), this, SLOT(sendMsg()));
}

void    GamesWindow::RecvSucces(QByteArray res)
{
  std::string succ1("");
  std::string succ2("");
  msgpack::unpacked result;
  msgpack::unpacker pac;

  std::cout << "RECV_SUCCES" << std::endl;
  pac.reserve_buffer(res.length());
  memcpy(pac.buffer(), res.data(), res.length());
  pac.buffer_consumed(res.length());
  if (pac.next(&result))
    {
      MasterData::RecvSucces recv("");
      pac.next(&result);
      result.get().convert(&recv);
      std::string succ(recv.succes);

      for (int i = 0; i < 25; i++)
	{
	  if (i < 20)
            succ1 += succ[i];
	  succ2 += succ[i + 20];
	}
      createTabSucces1(succ1);
      createTabSucces2(succ2);
    }
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
    _tab->addTab(_newsPage, "      News      ");

    QWebView *view = new QWebView(_newsPage);
    view->setGeometry(1,34,428,359);
    view->load(QUrl("https://google.fr/"));
    view->show();
}

void    GamesWindow::createTabServers()
{
    _serversPage = new QWidget(_tab);

    _match = new QPushButton("", _serversPage);
    _match->setFont(QFont("", 12, 0));
    _match->setGeometry(15, 42, 200, 50);
    _match->setStyleSheet("QWidget { background-image: url(img/matchmaking02.png); border: 0px; }");
    _match->setDefault(0);

    _join = new QPushButton("", _serversPage);
    _join->setFont(QFont("", 12, 0));
    _join->setGeometry(15, 335, 200, 50);
    _join->setStyleSheet("QWidget { background-image: url(img/join02.png); border: 0px; }");
    _join->setDefault(0);

    _refresh = new QPushButton("", _serversPage);
    _refresh->setFont(QFont("", 12, 0));
    _refresh->setGeometry(218, 42, 200, 50);
    _refresh->setStyleSheet("QWidget { background-image: url(img/refresh02.png); border: 0px; }");
    _refresh->setDefault(0);

    _iServ = new QLabel("<font color=\"#e7d593\">Liste des serveurs :</font>", _serversPage);
    _iServ->setGeometry(52, 95, 150, 20);
    _tab->addTab(_serversPage, "     Servers     ");
}

void    GamesWindow::createTabSucces1(std::string succ)
{
    std::string tmpSucc;
    std::string nameImg;

    _succesPage = new QWidget(_tab);
    _tab->insertTab(3, _succesPage, "  Succes All  ");

    for (int i = 0; i < 20; i++)
    {
        tmpSucc = "";
        tmpSucc += "[" + achivDivers[i].name + "]\n\n";
        tmpSucc += achivDivers[i].describe;
        nameImg = "img/allAchiv/divers/";
        nameImg += intToString(i + 1);
        nameImg += ".jpg";
        _imgSucc1[i] = new QLabel(_succesPage);
        _imgSucc1[i]->setPixmap(QPixmap(QString(nameImg.c_str())));
        _imgSucc1[i]->setGeometry((24 + (80 * (i % 5))), 56 + ((i / 5) * 85), 60, 60);
        _imgSucc1[i]->setToolTip(QString(tmpSucc.c_str()));
    }
    for (int i = 0; i < 20; i++)
    {
        _imgLock1[i] = new QLabel(_succesPage);
        _imgLock1[i]->setPixmap(QPixmap("img/allAchiv/lock.png"));
        _imgLock1[i]->setGeometry((24 + (80 * (i % 5))), 56 + ((i / 5) * 85), 60, 60);
        _imgLock1[i]->setToolTip("Locked Achivement !");
        if (succ[i] == '1')
            _imgLock1[i]->hide();
    }
}

void    GamesWindow::createTabSucces2(std::string succ)
{
    std::string tmpSucc;
    std::string nameImg;

    _succesPage = new QWidget(_tab);
    _tab->insertTab(3, _succesPage, " Succes Class ");

    for (int i = 0; i < 25; i++)
    {
        tmpSucc = "";
        tmpSucc += "[" + achivClass[i].name + "]\n\n";
        tmpSucc += achivClass[i].describe;
        nameImg = "img/allAchiv/class/";
        nameImg += intToString(i + 1);
        nameImg += ".jpg";
        _imgSucc2[i] = new QLabel(_succesPage);
        _imgSucc2[i]->setPixmap(QPixmap(QString(nameImg.c_str())));
        _imgSucc2[i]->setGeometry((24 + (80 * (i % 5))), 45 + ((i / 5) * 70), 60, 60);
        _imgSucc2[i]->setToolTip(QString(tmpSucc.c_str()));
    }
    for (int i = 0; i < 25; i++)
    {
        _imgLock2[i] = new QLabel(_succesPage);
        _imgLock2[i]->setPixmap(QPixmap("img/allAchiv/lock.png"));
        _imgLock2[i]->setGeometry((24 + (80 * (i % 5))), 45 + ((i / 5) * 70), 60, 60);
        _imgLock2[i]->setToolTip("Locked Achivement !");
        if (succ[i] == '1')
            _imgLock2[i]->hide();
    }
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
        _parent->getDataNet()->setServIP(serv.ip);
        _parent->getDataNet()->setServPort(serv.port);
        _parent->setClassWindow();
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
        QTextCursor c = _readChat->textCursor();
        c.movePosition(QTextCursor::End);
        _readChat->setTextCursor(c);
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
    std::cout << "RECV_DATA size" << res.length() << std::endl;
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
        case MasterData::Command::SUCCES:
            RecvSucces(res);
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
