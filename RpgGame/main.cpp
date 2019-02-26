#include "Gui/Forms/MainWindow.h"
#include <QApplication>


#include "Gui/Views/GraphicsViewGame.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //GraphicsViewGame graphicsViewGame(nullptr, 0);
    //graphicsViewGame.showFullScreen();

    return a.exec();
}
