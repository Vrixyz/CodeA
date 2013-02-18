#include "MyWindow.h"

int     main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MyWindow window(400, 400);
    window.show();

    return app.exec();
}
