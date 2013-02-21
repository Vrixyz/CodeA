#include "SuWindow.h"
#include <QtGui>

SuWindow::SuWindow(int size_x, int size_y, MyWindow *parent) : QDialog(parent, Qt::FramelessWindowHint)
{
    _parent = parent;
    setFixedSize(size_x, size_y);
    setStyleSheet("QWidget { background-image: url(img/bg-accwin.png); }");
    setSuPage();
}

SuWindow::~SuWindow()
{
}

void    SuWindow::setSuPage()
{
    creatFields4SuPage();

    _su = new QPushButton("Enregistrement", this);
    _su->setFont(QFont("", 12, 0));
    _su->setGeometry(100, 220, 200, 40);
    _su->setStyleSheet("color : #FFFFFF");
    QObject::connect(_su, SIGNAL(clicked()), this, SLOT(checkSu()));

    _back = new QPushButton("Retour", this);
    _back->setFont(QFont("", 12, 0));
    _back->setGeometry(100, 270, 200, 40);
    _back->setStyleSheet("color : #FFFFFF");
    QObject::connect(_back, SIGNAL(clicked()), _parent, SLOT(setAccWindow()));

    _SuQuit = new QPushButton("Quitter", this);
    _SuQuit->setFont(QFont("", 12, 0));
    _SuQuit->setGeometry(100, 320, 200, 40);
    _SuQuit->setStyleSheet("color : #FFFFFF");
    QObject::connect(_SuQuit, SIGNAL(clicked()), qApp, SLOT(quit()));
}

void    SuWindow::checkSu()
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

void    SuWindow::creatFields4SuPage()
{
    // Creations des 4 labels et des 4 champs de saisie
    _loginSuEdit = new QLineEdit(this);
    _passw1SuEdit = new QLineEdit(this);
    _passw2SuEdit = new QLineEdit(this);
    _mailEdit = new QLineEdit(this);
    _loginSuLabel = new QLabel("<font color=\"#FFFFFF\">&Login</font>:", this);
    _passw1SuLabel = new QLabel("<font color=\"#FFFFFF\">&Password</font>:", this);
    _passw2SuLabel = new QLabel("<font color=\"#FFFFFF\">&Password (conf.)</font>:", this);
    _mailLabel = new QLabel("<font color=\"#FFFFFF\">&Mail:</font>", this);

    _passw1SuEdit->setEchoMode(QLineEdit::Password);
    _passw2SuEdit->setEchoMode(QLineEdit::Password);

    _loginSuLabel->setAttribute(Qt::WA_TranslucentBackground);
    _passw1SuLabel->setAttribute(Qt::WA_TranslucentBackground);
    _passw2SuLabel->setAttribute(Qt::WA_TranslucentBackground);
    _mailLabel->setAttribute(Qt::WA_TranslucentBackground);

    _loginSuLabel->setGeometry(30, 50,120, 30);
    _passw1SuLabel->setGeometry(30, 85, 120, 30);
    _passw2SuLabel->setGeometry(30, 120, 120, 30);
    _mailLabel->setGeometry(30, 155, 120, 30);

    _loginSuEdit->setGeometry(160, 50, 210, 30);
    _passw1SuEdit->setGeometry(160, 85, 210, 30);
    _passw2SuEdit->setGeometry(160, 120, 210, 30);
    _mailEdit->setGeometry(160, 155, 210, 30);

    _loginSuLabel->setBuddy(_loginSuEdit);
    _passw1SuLabel->setBuddy(_passw1SuEdit);
    _passw2SuLabel->setBuddy(_passw2SuEdit);
    _mailLabel->setBuddy(_mailEdit);
}

void    SuWindow::RecvInfosClient()
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
