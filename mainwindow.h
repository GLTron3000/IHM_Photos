#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>

#include "explorer.h"
#include "visionneuse.h"
#include "models/imageswitcher.h"
#include "widgets/info.h"
#include "widgets/settings.h"
#include "widgets/about.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showVisio(ImageSwitcher *imageSwitcher);
    void showExplorer();
    void showSettings();
    void showAbout();
    void showHelp();
    void fullscreen();
    void quit();
    void switchExplorer(bool);

private:
    Ui::MainWindow *ui;
    Explorer *explorer;
    Visionneuse *visionneuse;
    Info *info;
    About *about;
    Settings *settings;
    void keyPressEvent(QKeyEvent *event);

    void setMenuAlbums();
    void setMenuAlbumImages();
    void setMenuVisionneuse();
};

#endif // MAINWINDOW_H
