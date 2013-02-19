#include "MyWindow.h"
#include "AccWindow.h"

int     main(int argc, char *argv[])
{
    QApplication    app(argc, argv);

    MyWindow window(400, 400);
    window.setCoWindow(400, 400);
    window.setPort(atoi(argv[1]));
//    window.show();
    window.getCoWindow()->show();
    return app.exec();
}
