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

    editeur = new EditeurImage();

    createExplorerToolBar();
    createVisioToolBar();
    createEditeurToolBar();

    ui->actionEditer_titres->setEnabled(false);
    ui->actionRetour->setEnabled(false);
    ui->actionRecharger->setEnabled(false);
    ui->actionNouvel_album->setEnabled(false);

    ui->actionZoomIn->setEnabled(false);
    ui->actionZoomOut->setEnabled(false);
    ui->actionRestaurer->setEnabled(false);
    ui->actionInfos->setEnabled(false);
    ui->actionEditer->setEnabled(false);

    ui->actionRogner->setEnabled(false);
    ui->actionRedimensionner->setEnabled(false);

    connect(explorer, SIGNAL(openImage(QString)), this, SLOT(showVisio(QString)));
    connect(editeur, SIGNAL(closeEditor()), this, SLOT(showVisio()));
    connect(ui->actionEditer, SIGNAL(triggered()), this, SLOT(showEditeur()));
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
    showVisio();
}

void MainWindow::showVisio(){
    explorerToolBar->hide();
    visioToolBar->show();
    editeurToolBar->hide();

    this->setCentralWidget(visionneuse);
    ui->actionZoomIn->setEnabled(true);
    ui->actionZoomOut->setEnabled(true);
    ui->actionRestaurer->setEnabled(true);
    ui->actionInfos->setEnabled(true);
    ui->actionEditer->setEnabled(true);
    ui->actionRogner->setEnabled(false);
    ui->actionRedimensionner->setEnabled(false);
    ui->actionEditer_titres->setEnabled(false);
}
void MainWindow::showExplorer(){
    explorerToolBar->show();
    visioToolBar->hide();
    editeurToolBar->hide();

    this->setCentralWidget(explorer);
    ui->actionZoomIn->setEnabled(false);
    ui->actionZoomOut->setEnabled(false);
    ui->actionRestaurer->setEnabled(false);
    ui->actionInfos->setEnabled(false);
    ui->actionEditer->setEnabled(false);
    ui->actionRogner->setEnabled(false);
    ui->actionRedimensionner->setEnabled(false);
    ui->actionEditer_titres->setEnabled(true);
    ui->actionRetour->setEnabled(true);
    ui->actionRecharger->setEnabled(true);
    ui->actionNouvel_album->setEnabled(true);
}

void MainWindow::showEditeur(){
    explorerToolBar->hide();
    visioToolBar->hide();
    editeurToolBar->show();

    editeur->setImage(visionneuse->imagePath);
    this->setCentralWidget(editeur);
    ui->actionRogner->setEnabled(true);
    ui->actionRedimensionner->setEnabled(true);
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

void MainWindow::createEditeurToolBar(){
    editeurToolBar = this->addToolBar(tr("Editeur"));
    editeurToolBar->addAction(ui->actionRogner);
    editeurToolBar->addAction(ui->actionRedimensionner);
}

void MainWindow::createVisioToolBar(){
    visioToolBar = this->addToolBar(tr("Visio"));
    visioToolBar->addAction(ui->actionRetour);
    visioToolBar->addAction(ui->actionEditer);
    visioToolBar->addAction(ui->actionInfos);
    visioToolBar->addAction(ui->actionZoomOut);
    visioToolBar->addAction(ui->actionZoomIn);
    visioToolBar->addAction(ui->actionRestaurer);
}
