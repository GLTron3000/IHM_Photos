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

    createExplorerToolBar();
    createVisioToolBar();

    ui->actionEditer_titres->setEnabled(false);
    ui->actionRetour->setEnabled(false);
    ui->actionRecharger->setEnabled(false);
    ui->actionNouvel_album->setEnabled(false);

    ui->actionZoomIn->setEnabled(false);
    ui->actionZoomOut->setEnabled(false);
    ui->actionRestaurer->setEnabled(false);
    ui->actionInfos->setEnabled(false);
    ui->actionRogner->setEnabled(false);
    ui->actionRedimensionner->setEnabled(false);
    ui->actionRetour->setEnabled(false);

    connect(explorer, SIGNAL(openImage(QString)), this, SLOT(showVisio(QString)));
    connect(ui->actionRetour, SIGNAL(triggered()), this, SLOT(showExplorer()));

    connect(ui->actionQuitter, SIGNAL(triggered()), this, SLOT(quit()));
    connect(ui->actionPlein_cran, SIGNAL(triggered()), this, SLOT(fullscreen()));

    connect(ui->actionNouvel_album, SIGNAL(triggered()), explorer, SLOT(addAlbum()));
    connect(ui->actionRecharger, SIGNAL(triggered()), explorer, SLOT(loadImages()));
    connect(ui->actionEditer_titres, SIGNAL(triggered()), explorer, SLOT(editTitle()));
    connect(ui->actionRetour_Album, SIGNAL(triggered()), explorer, SLOT(returnAlbum()));

    connect(ui->actionZoomIn, SIGNAL(triggered()), visionneuse, SLOT(zoomIn()));
    connect(ui->actionZoomOut, SIGNAL(triggered()), visionneuse, SLOT(zoomOut()));
    connect(ui->actionRestaurer, SIGNAL(triggered()), visionneuse, SLOT(restaurerTailleImg()));
    showExplorer();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showVisio(QString path){
    visionneuse->afficherImage(path);

    explorerToolBar->hide();
    visioToolBar->show();

    this->setCentralWidget(visionneuse);
    ui->actionEditer_titres->setEnabled(false);
    ui->actionRetour->setEnabled(false);
    ui->actionRecharger->setEnabled(false);
    ui->actionNouvel_album->setEnabled(false);

    ui->actionZoomIn->setEnabled(true);
    ui->actionZoomOut->setEnabled(true);
    ui->actionRestaurer->setEnabled(true);
    ui->actionInfos->setEnabled(true);
    ui->actionRogner->setEnabled(true);
    ui->actionRedimensionner->setEnabled(true);
    ui->actionRetour->setEnabled(true);
}

void MainWindow::showExplorer(){
    qDebug() << "SHOW EXPLORER";

    explorerToolBar->show();
    visioToolBar->hide();

    this->setCentralWidget(explorer);
    ui->actionEditer_titres->setEnabled(true);
    ui->actionRetour->setEnabled(true);
    ui->actionRecharger->setEnabled(true);
    ui->actionNouvel_album->setEnabled(true);

    ui->actionZoomIn->setEnabled(false);
    ui->actionZoomOut->setEnabled(false);
    ui->actionRestaurer->setEnabled(false);
    ui->actionInfos->setEnabled(false);
    ui->actionRogner->setEnabled(false);
    ui->actionRedimensionner->setEnabled(false);
    ui->actionRetour->setEnabled(false);
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

void MainWindow::createExplorerToolBar(){
    explorerToolBar = this->addToolBar(tr("Explorer"));
    explorerToolBar->addAction(ui->actionNouvel_album);
    explorerToolBar->addAction(ui->actionRecharger);
    explorerToolBar->addAction(ui->actionRetour_Album);
    explorerToolBar->addAction(ui->actionEditer_titres);
}

void MainWindow::createVisioToolBar(){
    visioToolBar = this->addToolBar(tr("Visio"));
    visioToolBar->addAction(ui->actionRetour);
    visioToolBar->addAction(ui->actionInfos);

    visioToolBar->addSeparator();
    visioToolBar->addAction(ui->actionZoomIn);
    visioToolBar->addAction(ui->actionZoomOut);
    visioToolBar->addAction(ui->actionRestaurer);

    visioToolBar->addSeparator();
    visioToolBar->addAction(ui->actionRogner);
    visioToolBar->addAction(ui->actionRedimensionner);
}
