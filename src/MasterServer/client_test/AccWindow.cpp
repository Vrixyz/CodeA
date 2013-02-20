#include "AccWindow.h"

AccWindow::AccWindow(int size_x, int size_y, MyWindow *parent) : QDialog(parent, 0)
{
    _parent = parent;
    setFixedSize(size_x, size_y);

    setTab();
    setCoPage();
    setSuPage();
}

AccWindow::~AccWindow()
{
}

void    AccWindow::setTab()
{
    _tabConnexion = new QTabWidget(this);
    _tabConnexion->setGeometry(0, 0, 400, 400);

    _page1 = new QWidget;
    _page2 = new QWidget;

    _tabConnexion->addTab(_page1, "Connexion");
    _tabConnexion->addTab(_page2, "Inscription");
    _tabConnexion->show();
}

void    AccWindow::setCoPage()
{
    creatFields4CoPage();

    _co = new QPushButton("Connexion", _page1);
    _co->setFont(QFont("", 12, 0));
    _co->setGeometry(100, 220, 200, 40);
    QObject::connect(_co, SIGNAL(clicked()), this, SLOT(checkCo()));

    _CoQuit = new QPushButton("Quitter", _page1);
    _CoQuit->setFont(QFont("", 12, 0));
    _CoQuit->setGeometry(100, 270, 200, 40);
    QObject::connect(_CoQuit, SIGNAL(clicked()), qApp, SLOT(quit()));
}

void    AccWindow::setSuPage()
{
    creatFields4SuPage();

    _su = new QPushButton("Enregistrement", _page2);
    _su->setFont(QFont("", 12, 0));
    _su->setGeometry(100, 220, 200, 40);
    QObject::connect(_su, SIGNAL(clicked()), this, SLOT(checkSu()));

    _SuQuit = new QPushButton("Quitter", _page2);
    _SuQuit->setFont(QFont("", 12, 0));
    _SuQuit->setGeometry(100, 270, 200, 40);
    QObject::connect(_SuQuit, SIGNAL(clicked()), qApp, SLOT(quit()));
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

void    AccWindow::checkSu()
{
    std::cout << std::endl << "TENTATIVE DE CREATION DE COMPTE";
    std::cout << std::endl << "Login : " << _loginSuEdit->text().toUtf8().constData();
    std::cout << std::endl << "Passw : " << _passw1SuEdit->text().toUtf8().constData();
    std::cout << std::endl << "Passw : " << _passw2SuEdit->text().toUtf8().constData();
    std::cout << std::endl << "AMail : " << _mailEdit->text().toUtf8().constData() << std::endl;

    _parent->getDataNet()->setNetwork(new Network("127.0.0.1", _parent->getPort()));
    _parent->getDataNet()->getNetwork()->connectToServer();

    msgpack::sbuffer sbuf;
    msgpack::packer<msgpack::sbuffer> packet(&sbuf);

    packet.pack((int)MasterData::Command::REGISTER_USER);
    MasterData::RegClient cli(_loginSuEdit->text().toUtf8().constData(), _passw1SuEdit->text().toUtf8().constData());
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

void    AccWindow::creatFields4SuPage()
{
    // Creations des 4 labels et des 4 champs de saisie
    _loginSuEdit = new QLineEdit(_page2);
    _passw1SuEdit = new QLineEdit(_page2);
    _passw2SuEdit = new QLineEdit(_page2);
    _mailEdit = new QLineEdit(_page2);
    _loginSuLabel = new QLabel("&Login:", _page2);
    _passw1SuLabel = new QLabel("&Password:", _page2);
    _passw2SuLabel = new QLabel("&Password (conf.):", _page2);
    _mailLabel = new QLabel("&Mail:", _page2);

    _passw1SuEdit->setEchoMode(QLineEdit::Password);
    _passw2SuEdit->setEchoMode(QLineEdit::Password);

    _loginSuLabel->setGeometry(30, 40,160, 30);
    _passw1SuLabel->setGeometry(30, 70, 160, 30);
    _passw2SuLabel->setGeometry(30, 100, 160, 30);
    _mailLabel->setGeometry(30, 130, 160, 30);

    _loginSuEdit->setGeometry(160, 40, 210, 30);
    _passw1SuEdit->setGeometry(160, 70, 210, 30);
    _passw2SuEdit->setGeometry(160, 100, 210, 30);
    _mailEdit->setGeometry(160, 130, 210, 30);

    _loginSuLabel->setBuddy(_loginSuEdit);
    _passw1SuLabel->setBuddy(_passw1SuEdit);
    _passw2SuLabel->setBuddy(_passw2SuEdit);
    _mailLabel->setBuddy(_mailEdit);
}

void    AccWindow::creatFields4CoPage()
{
    // Creations des deux labels et des deux champs de saisie
    _loginEdit = new QLineEdit(_page1);
    _passwEdit = new QLineEdit(_page1);
    _loginLabel = new QLabel("&Login:", _page1);
    _passwLabel = new QLabel("&Password:", _page1);

    _passwEdit->setEchoMode(QLineEdit::Password);

    _loginEdit->setGeometry(150, 80, 180, 30);
    _loginLabel->setGeometry(60, 80, 190, 30);
    _passwEdit->setGeometry(150, 130, 180, 30);
    _passwLabel->setGeometry(60, 130, 190, 30);

    _loginLabel->setBuddy(_loginEdit);
    _passwLabel->setBuddy(_passwEdit);
    _loginEdit->setText(QString("toto42"));
    _passwEdit->setText(QString("passw"));
}
