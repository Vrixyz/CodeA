#include "MyWindow.h"
#include "AccWindow.h"

int     main(int argc, char *argv[])
{
//    QApplication::setStyle(new QPlastiqueStyle);
    QApplication    app(argc, argv);

    MyWindow window(400, 400);
    window.setAccWindow();
    if (argc == 2)
        window.setPort(atoi(argv[1]));
    else
        window.setPort(4242);
    window.getAccWindow()->show();
    return app.exec();
}
