#include "explorer.h"

#include <QApplication>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Explorer w;

    QPixmap pixmap(":/ressources/images/splash.png");
    QSplashScreen splash(pixmap);
    splash.show();

    splash.showMessage("Chargement des images...", Qt::AlignBottom, Qt::white);

    a.processEvents();

    w.loadImages();

    w.showMaximized();

    splash.finish(&w);

    return a.exec();
}
