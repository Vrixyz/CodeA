#include "GamesWindow.h"
#include "MyItemLi.h"
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

    QObject::connect(_parent->getDataNet()->getNetwork()->getSock(), SIGNAL(readyRead()), this, SLOT(RecvData()));
    QObject::connect(_list, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(tryToCoGame()));
}

GamesWindow::~GamesWindow()
{
}

void    GamesWindow::setTabAndAll()
{
    _tab = new QTabWidget(this);

    _tab->setGeometry(50, 75, 425, 400);
    _tab->setStyleSheet(" QTabWidget::pane {"
" border-top: px solid #C2C7CB;"
" position: absolute;"
" top: -1em;"
" }"
" QTabWidget::tab-bar {"
" alignment: center;"
" }"
" QTabBar::tab {"
" background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
" stop: 0 #E1E1E1, stop: 0.4 #DDDDDD,"
" stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3);"
" border: 2px solid #C4C4C3;"
" border-bottom-color: #C2C7CB;"
" border-top-left-radius: 4px;"
" border-top-right-radius: 4px;"
" min-width: 8ex;"
" padding: 2px;"
" }"
" QTabBar::tab:selected, QTabBar::tab:hover {"
" background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
" stop: 0 #fafafa, stop: 0.4 #f4f4f4,"
" stop: 0.5 #e7e7e7, stop: 1.0 #fafafa);"
" }"
" QTabBar::tab:selected {"
" border-color: #9B9B9B;"
" border-bottom-color: #C2C7CB; }");

    createTabNews();
    createTabServers();
    createTabSucces();

    _list = new QListWidget(_serversPage);
    _list->setGeometry(10, 40, 380, 280);

    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::white);
    _list->setAutoFillBackground(true);
    _list->setPalette(Pal);
}

void    GamesWindow::createTabNews()
{
    _newsPage = new QWidget(_tab);
//    _newsPage->setStyleSheet("QWidget { background-image: url(img/bg-accwin.png); }");
    _tab->addTab(_newsPage, "      News      ");
}

void    GamesWindow::createTabServers()
{
    _serversPage = new QWidget(_tab);
<<<<<<< HEAD

    _tab->addTab(_serversPage, "Servers");
=======
    _tab->addTab(_serversPage, "      Servers      ");
>>>>>>> f465850c768343d03ff30c7e987c817d5d17be6b
}

void    GamesWindow::createTabSucces()
{
    _succesPage = new QWidget(_tab);
    _tab->addTab(_succesPage, "      Succes      ");
}

void    GamesWindow::tryToCoGame()
{
    int                                 nbGame;
    std::string                         toSend;
    std::string                         toPars;
    QList<QListWidgetItem *>            tmpList;
    QList<QListWidgetItem *>::Iterator  tmp;

    tmpList =_list->selectedItems();
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
      while (pac.next(&result))
	{
	  result.get().convert(&serv);
	  addToList(serv.id, serv.name);
	  std::cout << "ID " << serv.id << " NAME " << serv.name << std::endl;
	}
      _parent->getDataNet()->getNetwork()->getSock()->disconnect();
      _list->show();
    }
}

void    GamesWindow::RecvError(QByteArray res)
{
  msgpack::unpacked result;
  msgpack::unpacker pac;
  
  pac.reserve_buffer(res.length());
  memcpy(pac.buffer(), res.data(), res.length());
  pac.buffer_consumed(res.length());
  if (pac.next(&result))
    {
      MasterData::ErrorMsg err("");
      pac.next(&result);
      result.get().convert(&err);
      std::cerr << "Erreur : " << err.msg << std::endl;
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
