#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "widgets/explorer.h"
#include "widgets/visionneuse.h"
#include "widgets/editeurimage.h"
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
    void showVisio();
    void showExplorer();
    void showEditeur();
    void fullscreen();
    void quit();

private:
    Ui::MainWindow *ui;
    Explorer *explorer;
    Visionneuse *visionneuse;
    EditeurImage *editeur;

    void createExplorerToolBar();
    void createVisioToolBar();
    void createEditeurToolBar();

    QToolBar *explorerToolBar;
    QToolBar *visioToolBar;
    QToolBar *editeurToolBar;

};

#endif // MAINWINDOW_H
