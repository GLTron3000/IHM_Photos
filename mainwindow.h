#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "widgets/explorer.h"
#include "widgets/visionneuse.h"
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
    void showVisio(QString path);
    void showExplorer();
    void fullscreen();
    void quit();

private:
    Ui::MainWindow *ui;
    Explorer *explorer;
    Visionneuse *visionneuse;

    void createExplorerToolBar();
    void createVisioToolBar();

    QToolBar *explorerToolBar;
    QToolBar *visioToolBar;

};

#endif // MAINWINDOW_H
