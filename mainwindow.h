#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "explorerb.h"
#include "widgets/visionneuse.h"
#include "widgets/info.h"

#include <QToolBar>

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
    void showVisio(Image image);
    void showExplorer();
    void showSettings();
    void fullscreen();
    void quit();

private:
    Ui::MainWindow *ui;
    ExplorerB *explorer;
    Visionneuse *visionneuse;

    void createExplorerToolBar();
    void createVisioToolBar();

    void setToolBar(bool isExplorer);

    QToolBar *explorerToolBar;
    QToolBar *visioToolBar;

    Info *info;

};

#endif // MAINWINDOW_H
