#include "mainview.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap("/home/pi/Projects/RaspGui/GUI_loading.PNG"));
    splash->showFullScreen();

    MainView w;

    QTimer::singleShot(6000,splash,SLOT(close()));
    QTimer::singleShot(6000,&w,SLOT(showFullScreen()));
    QTimer::singleShot(6500,&w,SLOT(generateRooms()));

    //w.showFullScreen();
    return a.exec();
}
