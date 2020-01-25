#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "explorer.h"
#include "visionneuse.h"

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
    void reload();
    void quit();

private:
    Ui::MainWindow *ui;
    Explorer *explorer;
    Visionneuse *visionneuse;
};

#endif // MAINWINDOW_H
