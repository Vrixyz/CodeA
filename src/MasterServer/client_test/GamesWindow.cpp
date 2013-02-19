#include "GamesWindow.h"

GamesWindow::GamesWindow()
{
}

//void    AccWindow::initGames()
//{
//    t_game *game = new t_game[25];
//    for (int i = 0; i < 25; i++)
//    {
//        game[i].id = i;
//        game[i].size = 4;
//        game[i].name = intToString(game[i].id);
//        game[i].name += " | ";
//        game[i].name += "Game";
//        allGames.push_back(game[i]);
//    }
//}

//void    AccWindow::showGames()
//{
//    std::string string;
//    std::list<t_game>::iterator tmp;
//    QListWidgetItem*    toAdd;

//    list = new QListWidget(this);
//    for (tmp = allGames.begin(); tmp != allGames.end(); tmp++)
//    {
//        toAdd = new QListWidgetItem();
//        string = "";
//        string += tmp->name;
//        toAdd->setText(string.c_str());
//        list->addItem(toAdd);
//    }
//    list->setGeometry(10, 10, 380, 330);
//    list->show();
//    QObject::connect(list, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(tryCoToGame()));
//}

//void    AccWindow::tryCoToGame()
//{
//    std::string toSend;
//    std::string toPars;
//    QList<QListWidgetItem *> tmpList;
//    QList<QListWidgetItem *>::Iterator tmp;

//    tmpList = list->selectedItems();
//    tmp = tmpList.begin();
//    toPars = (*tmp)->text().toUtf8().constData();
//    toSend = "";
//    for (unsigned int i = 0; i < toPars.size() && (toPars[i] <= '9' && toPars[i] >= '0'); i++)
//        toSend += toPars[i];

//    std::cout << "TRY DE CONNEXION A LA GAME ---> " << stringToInt(toSend) << std::endl;
//}

