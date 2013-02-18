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

    std::cout << "dat login " << toSendLogin << " -- dat passw " << toSendPassw << std::endl;

    // FONCTION OU SEND LES MACHINS POUR LES TRUCS DE CONNEXION AU BORDEL

    if ((toSendLogin.compare("toto42") == 0) && (toSendPassw.compare("passw") == 0))
        cleanAndShow();
    passwEdit->clear();
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
    t_game *game = new t_game[10];
    for (int i = 0; i < 10; i++)
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

    list = new QListWidget(this);
    for (tmp = allGames.begin(); tmp != allGames.end(); tmp++)
    {
        string = "";
        string += tmp->name;
        list->addItem(new QListWidgetItem(string.c_str()));
    }
    list->setGeometry(10, 10, 380, 330);
    list->show();
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
