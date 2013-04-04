#include "MyWindow.h"
#include "AccWindow.h"

int     main(int argc, char *argv[])
{
//    QApplication::setStyle(new QPlastiqueStyle);
    QApplication    app(argc, argv);

    MyWindow window(400, 400);
    window.setAccWindow();
    if (argc == 3)
      {
	window.setIP(argv[1]);
        window.setPort(atoi(argv[2]));
      }
    else
      {
	window.setIP("127.0.0.1");
        window.setPort(4242);
      }
    window.getAccWindow()->show();
    return app.exec();
}
