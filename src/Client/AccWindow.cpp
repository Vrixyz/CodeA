#include "AccWindow.h"

AccWindow::AccWindow(int size_x, int size_y, MyWindow *parent) : QDialog(parent, Qt::FramelessWindowHint)
{
    _parent = parent;
    setFixedSize(size_x, size_y);

    this->move(600, 250);

    setObjectName("accwin");
    setStyleSheet("#accwin { background-image: url(img/bg-test.png); }");

    setCoPage();
}

AccWindow::~AccWindow()
{
}

void    AccWindow::setCoPage()
{
    creatFields4CoPage();

    _CoQuit = new QPushButton("", this);
    _CoQuit->setFont(QFont("", 12, 0));
    _CoQuit->setGeometry(100, 320, 200, 40);
    _CoQuit->setStyleSheet("QWidget { background-image: url(img/quitter.png); border: 0px; }");
    _CoQuit->setDefault(0);
    QObject::connect(_CoQuit, SIGNAL(clicked()), qApp, SLOT(quit()));

    _co = new QPushButton("", this);
    _co->setFont(QFont("", 12, 0));
    _co->setGeometry(100, 220, 200, 40);
    _co->setStyleSheet("QWidget { background-image: url(img/connexion.png); border: 0px; }");
    _co->setDefault(0);
    QObject::connect(_co, SIGNAL(clicked()), this, SLOT(checkCo()));

    _su = new QPushButton("", this);
    _su->setFont(QFont("", 12, 0));
    _su->setGeometry(100, 270, 200, 40);
    _su->setStyleSheet("color : #FFFFFF");
    _su->setStyleSheet("QWidget { background-image: url(img/inscription.png); border: 0px; }");
    _su->setDefault(0);
    QObject::connect(_su, SIGNAL(clicked()), _parent, SLOT(setSuWindow()));
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
    _parent->getDataNet()->setNetwork(new Network(_parent->getIP(), _parent->getPort()));
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
            _parent->getDataNet()->setLogin(info.name);
            _parent->getDataNet()->getNetwork()->getSock()->disconnect();
            _parent->setGamesWindow();
	  }
        else if (idData == MasterData::Command::ERROR)
	  {
	    MasterData::ErrorMsg err("");
            pac.next(&result);
            result.get().convert(&err);
            QMessageBox::warning(this, tr("Erreur"), tr(err.msg.c_str()));
	  }
	else
	  {
	    QMessageBox::warning(this, tr("Erreur"), tr("Master non conforme"));
	    exit(0);
	  }
    }
}

void    AccWindow::creatFields4CoPage()
{
    // Creations des deux labels et des deux champs de saisie
    _loginEdit = new QLineEdit(this);
    _passwEdit = new QLineEdit(this);
    _loginLabel = new QLabel("<font color=\"#000000\">&Login</font>:", this);
    _passwLabel = new QLabel("<font color=\"#000000\">&Password:</font>", this);

    _passwEdit->setEchoMode(QLineEdit::Password);

    _passwLabel->setGeometry(60, 160, 90, 30);
    _loginLabel->setGeometry(60, 120, 90, 30);
    _passwEdit->setGeometry(150, 160, 180, 30);
    _loginEdit->setGeometry(150, 120, 180, 30);

    _loginLabel->setAttribute(Qt::WA_TranslucentBackground);
    _passwLabel->setAttribute(Qt::WA_TranslucentBackground);

    _loginEdit->setStyleSheet("QWidget { background-image: url(img/login_co.png); border :0; color: black; } ");
    _passwEdit->setStyleSheet("QWidget { background-image: url(img/pass_co.png); border :0; color: black; } ");
    _loginEdit->setAlignment(Qt::AlignHCenter);
    _passwEdit->setAlignment(Qt::AlignHCenter);

    _loginLabel->setBuddy(_loginEdit);
    _passwLabel->setBuddy(_passwEdit);
    _loginEdit->setText(QString("toto42"));
    _passwEdit->setText(QString("passw"));

    QObject::connect(_loginEdit, SIGNAL(returnPressed()), this, SLOT(checkCo()));
    QObject::connect(_passwEdit, SIGNAL(returnPressed()), this, SLOT(checkCo()));
}
