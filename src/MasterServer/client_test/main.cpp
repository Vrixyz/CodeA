#include "MyWindow.h"
#include "AccWindow.h"

int     main(int argc, char *argv[])
{
    QApplication    app(argc, argv);

    MyWindow window(400, 400);
    window.setCoWindow(400, 400);
    if (argc == 2)
        window.setPort(atoi(argv[1]));
    else
        window.setPort(4242);
    window.getCoWindow()->show();
    return app.exec();
}
