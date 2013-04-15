#include "SuWindow.h"
#include <QtGui>

SuWindow::SuWindow(int size_x, int size_y, MyWindow *parent) : QDialog(parent, Qt::FramelessWindowHint)
{
    _parent = parent;
    setFixedSize(size_x, size_y);

    this->move(600, 250);

    setObjectName("suwindow");
    setStyleSheet("#suwindow { background-image: url(img/bg-test.png); }");

    setSuPage();
}

SuWindow::~SuWindow()
{
}

void    SuWindow::setSuPage()
{
    creatFields4SuPage();

    _su = new QPushButton("", this);
    _su->setFont(QFont("", 12, 0));
    _su->setGeometry(100, 220, 200, 40);
    _su->setStyleSheet("QWidget { background-image: url(img/enregistrement.png); border :0; } ");
    QObject::connect(_su, SIGNAL(clicked()), this, SLOT(checkSu()));

    _back = new QPushButton("", this);
    _back->setFont(QFont("", 12, 0));
    _back->setGeometry(100, 270, 200, 40);
    _back->setStyleSheet("QWidget { background-image: url(img/retour.png); border :0; } ");
    QObject::connect(_back, SIGNAL(clicked()), _parent, SLOT(setAccWindow()));

    _SuQuit = new QPushButton("", this);
    _SuQuit->setFont(QFont("", 12, 0));
    _SuQuit->setGeometry(100, 320, 200, 40);
    _SuQuit->setStyleSheet("QWidget { background-image: url(img/quitter.png); border :0; } ");
    QObject::connect(_SuQuit, SIGNAL(clicked()), qApp, SLOT(quit()));
}

void    SuWindow::checkSu()
{
    std::cout << std::endl << "TENTATIVE DE CREATION DE COMPTE";
    std::cout << std::endl << "Login : " << _loginSuEdit->text().toUtf8().constData();
    std::cout << std::endl << "Passw : " << _passw1SuEdit->text().toUtf8().constData();
    std::cout << std::endl << "Passw : " << _passw2SuEdit->text().toUtf8().constData();
    std::cout << std::endl << "AMail : " << _mailEdit->text().toUtf8().constData() << std::endl;

    if ((_passw1SuEdit->text().size() == 0) || (_passw2SuEdit->text().size() == 0) || (_mailEdit->text().size() == 0) || (_loginSuEdit->text().size() == 0))
      {
        QMessageBox::warning(this, tr("Erreur"), tr("Tous les champs ne sont pas remplis."));
        _passw1SuEdit->clear();
        _passw2SuEdit->clear();
      }
    else if (_passw1SuEdit->text() == _passw2SuEdit->text())
    {
        _parent->getDataNet()->setNetwork(new Network(_parent->getIP(), _parent->getPort()));
        _parent->getDataNet()->getNetwork()->connectToServer();

        msgpack::sbuffer sbuf;
        msgpack::packer<msgpack::sbuffer> packet(&sbuf);

        packet.pack((int)MasterData::Command::REGISTER_USER);
        MasterData::RegClient cli(_loginSuEdit->text().toUtf8().constData(), _passw1SuEdit->text().toUtf8().constData());
        packet.pack(cli);

        _parent->getDataNet()->getNetwork()->sendToServer(sbuf);

        QObject::connect(_parent->getDataNet()->getNetwork()->getSock(), SIGNAL(readyRead()), this, SLOT(RecvInfosClient()));
    }
    else
    {
        QMessageBox::warning(this, tr("Erreur"), tr("Les mots de passe ne correspondent pas."));
        _passw1SuEdit->clear();
        _passw2SuEdit->clear();
    }
}

void    SuWindow::creatFields4SuPage()
{
    // Creations des 4 labels et des 4 champs de saisie
    _loginSuEdit = new QLineEdit(this);
    _passw1SuEdit = new QLineEdit(this);
    _passw2SuEdit = new QLineEdit(this);
    _mailEdit = new QLineEdit(this);
    _loginSuLabel = new QLabel("<font color=\"#000000\">&Login</font>:", this);
    _passw1SuLabel = new QLabel("<font color=\"#000000\">&Password</font>:", this);
    _passw2SuLabel = new QLabel("<font color=\"#000000\">&Password (conf.)</font>:", this);
    _mailLabel = new QLabel("<font color=\"#000000\">&Mail:</font>", this);

    _passw1SuEdit->setEchoMode(QLineEdit::Password);
    _passw2SuEdit->setEchoMode(QLineEdit::Password);

    _loginSuLabel->setAttribute(Qt::WA_TranslucentBackground);
    _passw1SuLabel->setAttribute(Qt::WA_TranslucentBackground);
    _passw2SuLabel->setAttribute(Qt::WA_TranslucentBackground);
    _mailLabel->setAttribute(Qt::WA_TranslucentBackground);


    _loginSuLabel->setGeometry(30, 100,120, 25);
    _passw1SuLabel->setGeometry(30, 130, 120, 25);
    _passw2SuLabel->setGeometry(30, 160, 120, 25);
    _mailLabel->setGeometry(30, 190, 120, 25);

    _loginSuEdit->setGeometry(160, 100, 210, 25);
    _passw1SuEdit->setGeometry(160, 130, 210, 25);
    _passw2SuEdit->setGeometry(160, 160, 210, 25);
    _mailEdit->setGeometry(160, 190, 210, 25);

    _loginSuLabel->setBuddy(_loginSuEdit);
    _passw1SuLabel->setBuddy(_passw1SuEdit);
    _passw2SuLabel->setBuddy(_passw2SuEdit);
    _mailLabel->setBuddy(_mailEdit);

    _loginSuEdit->setAlignment(Qt::AlignHCenter);
    _passw1SuEdit->setAlignment(Qt::AlignHCenter);
    _passw2SuEdit->setAlignment(Qt::AlignHCenter);
    _mailEdit->setAlignment(Qt::AlignHCenter);

    _loginSuEdit->setStyleSheet("QWidget { background-image: url(img/login_su.png); border :0; color: black; } ");
    _passw1SuEdit->setStyleSheet("QWidget { background-image: url(img/pass1_su.png); border :0; color: black; } ");
    _passw2SuEdit->setStyleSheet("QWidget { background-image: url(img/pass2_su.png); border :0; color: black; } ");
    _mailEdit->setStyleSheet("QWidget { background-image: url(img/mail_su.png); border :0; color: black; } ");
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
            QMessageBox::warning(this, tr("Erreur"), tr("Master non conforme"));
            std::cerr << "Erreur connexion : " << err.msg << std::endl;
        }
        else
        {
            QMessageBox::warning(this, tr("Erreur"), tr("Master non conforme"));
            exit(0);
        }
    }
}
