#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Client");
    MainWindow w;
    w.showFullScreen();
    
    return a.exec();
}
