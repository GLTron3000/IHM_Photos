#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>

#include "explorer.h"
#include "visionneuse.h"
#include "models/imageswitcher.h"
#include "widgets/info.h"

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
    void fullscreen();
    void quit();

private:
    Ui::MainWindow *ui;
    Explorer *explorer;
    Visionneuse *visionneuse;
    Info *info;
    void keyPressEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H
