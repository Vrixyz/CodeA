#include "GamesWindow.h"
#include "Define.h"

GamesWindow::GamesWindow(int size_x, int size_y, MyWindow *parent) : QDialog(parent, Qt::FramelessWindowHint)
{
    _parent = parent;
    setFixedSize(size_x, size_y);

    setStyleSheet("QWidget { background-image: url(img/bg-accwin.png); }");

    _quit = new QPushButton("Quitter", this);
    _quit->setFont(QFont("", 12, 0));
    _quit->setStyleSheet("color : #FFFFFF");
    _quit->setGeometry(100, 340, 200, 40);
    QObject::connect(_quit, SIGNAL(clicked()), qApp, SLOT(quit()));

    _list = new QListWidget(this);
    _list->setGeometry(10, 40, 380, 280);
    _list->setAttribute(Qt::WA_TranslucentBackground);

    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::black);
    _list->setAutoFillBackground(true);
    _list->setPalette(Pal);

    _servLabel = new QLabel(this, 0);
    _servLabel->setFont(QFont("", 14, 0));
    _servLabel->setText("<font color=\"#FFFFFF\">Liste des Serveurs</font>");
    _servLabel->setAlignment(Qt::AlignCenter);
    _servLabel->setGeometry(0, 0, 400, 40);
    _servLabel->show();

    msgpack::sbuffer sbuf;
    msgpack::packer<msgpack::sbuffer> packet(&sbuf);

    packet.pack((int)MasterData::Command::ASK_SERVER_LIST);

    _parent->getDataNet()->getNetwork()->sendToServer(sbuf);

    QObject::connect(_parent->getDataNet()->getNetwork()->getSock(), SIGNAL(readyRead()), this, SLOT(RecvData()));
    QObject::connect(_list, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(tryToCoGame()));
}

GamesWindow::~GamesWindow()
{
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


    // ON ENVOI AU SERVEUR LE CHOIX DE GAME
    msgpack::sbuffer sbuf;
    msgpack::packer<msgpack::sbuffer> packet(&sbuf);

    packet.pack((int)MasterData::Command::REQUEST_SERVER);
    packet.pack(nbGame);

    _parent->getDataNet()->getNetwork()->sendToServer(sbuf);
    //    std::cout << "TRY DE CONNEXION A LA GAME ---> " << nbGame << std::endl;
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
      pac.next(&result);
      //PARSER LA STRUCT D'infos SERVEUR ET FAIRE LE BORDEL QUE DORIAN DOIT FAIRE!
      //
      //result.get().convert(&idData);
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
    QListWidgetItem*    item;

    labelName = "";
    labelName += intToString(id);
    labelName += " | ";
    labelName += name;
    QString toto(labelName.c_str());
    item = new QListWidgetItem(toto);
    _list->addItem(item);
}
