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
    void showExplorer();
    void showEditeur();
    void fullscreen();
    void reload();
    void quit();

private:
    Ui::MainWindow *ui;
    Explorer *explorer;
    Visionneuse *visionneuse;
    EditeurImage *editeur;
};

#endif // MAINWINDOW_H
