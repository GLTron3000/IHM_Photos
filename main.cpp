#include "mainwindow.h"

#include <QApplication>
#include <QSplashScreen>
#include "models/image.h"

int main(int argc, char *argv[])
{
    Image::initImage();

    QApplication a(argc, argv);
    MainWindow mainWindow;    

    QPixmap pixmap(":/ressources/images/splash.png");
    QSplashScreen splash(pixmap);
    splash.show();

    splash.showMessage("Chargement des images...", Qt::AlignBottom, Qt::white);

    a.processEvents();

    mainWindow.showMaximized();

    splash.finish(&mainWindow);

    return a.exec();
}
