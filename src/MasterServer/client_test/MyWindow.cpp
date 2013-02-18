#include "MyWindow.h"

MyWindow::MyWindow(int size_x, int size_y) : QWidget()
{
    setFixedSize(size_x, size_y);

    createCo(100, 220, 200, 40);
    createQuit(100, 270, 200, 40);
    creatFields();
}

void    MyWindow::checkCo()
{
    QString login;
    QString passw;

    std::string toSendLogin;
    std::string toSendPassw;

    login = loginEdit->text();
    passw = passwEdit->text();

    toSendLogin = login.toUtf8().constData();
    toSendPassw = passw.toUtf8().constData();
    _soc = new Network("127.0.0.1", _port);
    _soc->connectToServer();

    msgpack::sbuffer sbuf;
    msgpack::packer<msgpack::sbuffer> packet(&sbuf);

    packet.pack((int)MasterData::Command::CONNECT_USER);
    MasterData::CoClient cli(toSendLogin, toSendPassw);
    packet.pack(cli);

    _soc->sendToServer(sbuf);
    //    std::cout << "dat login " << toSendLogin << " -- dat passw " << toSendPassw << std::endl;


    // if ((toSendLogin.compare("toto42") == 0) && (toSendPassw.compare("passw") == 0))
    //        cleanAndShow();
    // passwEdit->clear();
}

void    MyWindow::cleanAndShow()
{
    co->close();
    loginEdit->close();
    passwEdit->close();
    loginLabel->close();
    passwLabel->close();
    quit->setGeometry(100, 350, 200, 40);
    initGames();
    showGames();
}

void    MyWindow::initGames()
{
    t_game *game = new t_game[25];
    for (int i = 0; i < 25; i++)
    {
        game[i].id = i;
        game[i].size = 4;
        game[i].name = intToString(game[i].id);
        game[i].name += " | ";
        game[i].name += "Game";
        allGames.push_back(game[i]);
    }
}

void    MyWindow::showGames()
{
    std::string string;
    std::list<t_game>::iterator tmp;
    QListWidgetItem*    toAdd;

    list = new QListWidget(this);
    for (tmp = allGames.begin(); tmp != allGames.end(); tmp++)
    {
        toAdd = new QListWidgetItem();
        string = "";
        string += tmp->name;
        toAdd->setText(string.c_str());
        list->addItem(toAdd);
    }
    list->setGeometry(10, 10, 380, 330);
    list->show();
    QObject::connect(list, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(tryCoToGame()));
}

void    MyWindow::tryCoToGame()
{
    std::string toSend;
    std::string toPars;
    QList<QListWidgetItem *> tmpList;
    QList<QListWidgetItem *>::Iterator tmp;

    tmpList = list->selectedItems();
    tmp = tmpList.begin();
    toPars = (*tmp)->text().toUtf8().constData();
    toSend = "";
    for (unsigned int i = 0; i < toPars.size() && (toPars[i] <= '9' && toPars[i] >= '0'); i++)
        toSend += toPars[i];

    std::cout << "TRY DE CONNEXION A LA GAME ---> " << stringToInt(toSend) << std::endl;
}

void    MyWindow::createQuit(int x, int y, int size_x, int size_y)
{
    quit = new QPushButton("Quitter", this);
    quit->setFont(QFont("", 12, 0));
    quit->setGeometry(x, y, size_x, size_y);
    QObject::connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));
}

void    MyWindow::createCo(int x, int y, int size_x, int size_y)
{
    co = new QPushButton("Connexion", this);
    co->setFont(QFont("", 12, 0));
    co->setGeometry(x, y, size_x, size_y);
    QObject::connect(co, SIGNAL(clicked()), this, SLOT(checkCo()));
}

void    MyWindow::creatFields()
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
