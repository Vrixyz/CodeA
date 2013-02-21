#include "AccWindow.h"

AccWindow::AccWindow(int size_x, int size_y, MyWindow *parent) : QDialog(parent, Qt::FramelessWindowHint)
{
    _parent = parent;
    setFixedSize(size_x, size_y);
    setStyleSheet("QWidget { background-image: url(img/bg-accwin.png); }");
    setCoPage();
}

AccWindow::~AccWindow()
{
}

void    AccWindow::setCoPage()
{
    creatFields4CoPage();

    _co = new QPushButton("Connexion", this);
    _co->setFont(QFont("", 12, 0));
    _co->setGeometry(100, 220, 200, 40);
    _co->setStyleSheet("color : #FFFFFF");
    QObject::connect(_co, SIGNAL(clicked()), this, SLOT(checkCo()));

    _su = new QPushButton("Inscription", this);
    _su->setFont(QFont("", 12, 0));
    _su->setGeometry(100, 270, 200, 40);
    _su->setStyleSheet("color : #FFFFFF");
    QObject::connect(_su, SIGNAL(clicked()), _parent, SLOT(setSuWindow()));

    _CoQuit = new QPushButton("Quitter", this);
    _CoQuit->setFont(QFont("", 12, 0));
    _CoQuit->setGeometry(100, 320, 200, 40);
    _CoQuit->setStyleSheet("color : #FFFFFF");
    QObject::connect(_CoQuit, SIGNAL(clicked()), qApp, SLOT(quit()));
}

void    AccWindow::checkCo()
{
    QString login;
    QString passw;

    std::string toSendLogin;
    std::string toSendPassw;

    login = _loginEdit->text();
    passw = _passwEdit->text();

    toSendLogin = login.toUtf8().constData();
    toSendPassw = passw.toUtf8().constData();
    _parent->getDataNet()->setNetwork(new Network("127.0.0.1", _parent->getPort()));
    _parent->getDataNet()->getNetwork()->connectToServer();

    msgpack::sbuffer sbuf;
    msgpack::packer<msgpack::sbuffer> packet(&sbuf);

    packet.pack((int)MasterData::Command::CONNECT_USER);
    MasterData::CoClient cli(toSendLogin, toSendPassw);
    packet.pack(cli);

    _parent->getDataNet()->getNetwork()->sendToServer(sbuf);

    QObject::connect(_parent->getDataNet()->getNetwork()->getSock(), SIGNAL(readyRead()), this, SLOT(RecvInfosClient()));
}

void    AccWindow::RecvInfosClient()
{
    QByteArray res;
    msgpack::unpacked result;
    msgpack::unpacker pac;

    res = _parent->getDataNet()->getNetwork()->ReceiveFromServer();
    std::cout << "INFO SIZE " << res.length() << std::endl;


    pac.reserve_buffer(res.length());
    memcpy(pac.buffer(), res.data(), res.length());
    pac.buffer_consumed(res.length());
    if (pac.next(&result))
    {
        int idData;
        result.get().convert(&idData);
        if (idData == MasterData::Command::INFOS_CLIENT)
        {
            MasterData::InfosClient info("");
            pac.next(&result);
            result.get().convert(&info);
            std::cout << "CONNEXION DONE de " << info.name << std::endl;
            _parent->getDataNet()->getNetwork()->getSock()->disconnect();
            _parent->setGamesWindow();
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

void    AccWindow::creatFields4CoPage()
{
    // Creations des deux labels et des deux champs de saisie
    _loginEdit = new QLineEdit(this);
    _passwEdit = new QLineEdit(this);
    _loginLabel = new QLabel("<font color=\"#FFFFFF\">&Login</font>:", this);
    _passwLabel = new QLabel("<font color=\"#FFFFFF\">&Password:</font>", this);

    _passwEdit->setEchoMode(QLineEdit::Password);
    _loginEdit->setGeometry(150, 80, 180, 30);
    _loginLabel->setGeometry(60, 80, 90, 30);
    _passwEdit->setGeometry(150, 130, 180, 30);
    _passwLabel->setGeometry(60, 130, 90, 30);


    _loginLabel->setAttribute(Qt::WA_TranslucentBackground);
    _passwLabel->setAttribute(Qt::WA_TranslucentBackground);

    _loginLabel->setBuddy(_loginEdit);
    _passwLabel->setBuddy(_passwEdit);
    _loginEdit->setText(QString("toto42"));
    _passwEdit->setText(QString("passw"));
}
