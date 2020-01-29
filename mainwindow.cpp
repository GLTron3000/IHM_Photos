#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    explorer = new Explorer();
    explorer->loadImages();

    visionneuse = new Visionneuse();

    connect(explorer, SIGNAL(openImage(QString)), this, SLOT(showVisio(QString)));
    connect(ui->actionRecharger, SIGNAL(triggered()), this, SLOT(reload()));
    connect(ui->actionQuitter, SIGNAL(triggered()), this, SLOT(quit()));
    connect(ui->actionPlein_cran, SIGNAL(triggered()), this, SLOT(fullscreen()));
    showExplorer();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showVisio(QString path){
    this->setCentralWidget(visionneuse);
    visionneuse->afficherImage(path);
}

void MainWindow::showExplorer(){
    this->setCentralWidget(explorer);
}

void MainWindow::reload(){
    explorer->loadImages();
}

void MainWindow::quit(){
    QApplication::quit();
}

void MainWindow::fullscreen(){
    if(ui->actionPlein_cran->isChecked()){
        this->setWindowState(Qt::WindowFullScreen);
    }else{
        this->setWindowState(Qt::WindowMaximized);
    }
}