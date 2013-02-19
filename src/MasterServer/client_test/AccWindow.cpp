#include "AccWindow.h"
#include "MyWindow.h"

AccWindow::AccWindow(int size_x, int size_y, MyWindow *parent) : QDialog(parent, 0)
{
    _parent = parent;
    setFixedSize(size_x, size_y);

    creatFields();

    co = new QPushButton("Connexion", this);
    co->setFont(QFont("", 12, 0));
    co->setGeometry(100, 220, 200, 40);
    QObject::connect(co, SIGNAL(clicked()), this, SLOT(checkCo()));

    quit = new QPushButton("Quitter", this);
    quit->setFont(QFont("", 12, 0));
    quit->setGeometry(100, 270, 200, 40);
    QObject::connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));
}

AccWindow::~AccWindow()
{
}

void    AccWindow::checkCo()
{
    QString login;
    QString passw;

    std::string toSendLogin;
    std::string toSendPassw;

    login = loginEdit->text();
    passw = passwEdit->text();

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
}

void    AccWindow::creatFields()
{
    // Creations des deux labels et des deux champs de saisie
    loginEdit = new QLineEdit(this);
    passwEdit = new QLineEdit(this);
    loginLabel = new QLabel("&Login:", this);
    passwLabel = new QLabel("&Password:", this);

    passwEdit->setEchoMode(QLineEdit::Password);

    loginEdit->setGeometry(150, 80, 180, 30);
    loginLabel->setGeometry(60, 80, 190, 30);
    passwEdit->setGeometry(150, 130, 180, 30);
    passwLabel->setGeometry(60, 130, 190, 30);

    loginLabel->setBuddy(loginEdit);
    passwLabel->setBuddy(passwEdit);
    loginEdit->setText(QString("toto42"));
    passwEdit->setText(QString("passw"));
}
