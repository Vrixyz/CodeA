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

    QObject::connect(_parent->getDataNet()->getNetwork()->getSock(), SIGNAL(readyRead()), this, SLOT(RecvList()));
}

GamesWindow::~GamesWindow()
{
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
