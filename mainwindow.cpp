#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "widgets/settings.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //createExplorerToolBar();
    //createVisioToolBar();

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
    ui->actionNoter->setEnabled(false);

    connect(ui->actionRetour, SIGNAL(triggered()), this, SLOT(showExplorer()));
    connect(ui->actionPr_f_rences, SIGNAL(triggered()), this, SLOT(showSettings()));

    connect(ui->actionQuitter, SIGNAL(triggered()), this, SLOT(quit()));
    connect(ui->actionPlein_cran, SIGNAL(triggered()), this, SLOT(fullscreen()));


    showExplorer();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showVisio(ImageSwitcher *imageSwitcher){
    qDebug() << "SHOW VISIO " << imageSwitcher->getImage().path;
    visionneuse = new Visionneuse(nullptr, imageSwitcher);
    visionneuse->afficherImage(imageSwitcher->getImage().path);

    connect(visionneuse, SIGNAL(closeVisio()), this, SLOT(showExplorer()));

    this->setCentralWidget(visionneuse);
    setToolBar(false);
}

void MainWindow::showExplorer(){
    qDebug() << "SHOW EXPLORER";

    explorer = new Explorer();
    connect(explorer, SIGNAL(openImageFromAlbum(ImageSwitcher*)), this, SLOT(showVisio(ImageSwitcher*)));
    setToolBar(true);
    this->setCentralWidget(explorer);
}

void MainWindow::showSettings(){
    qDebug() << "SHOW SETTINGS";
    Settings *settings = new Settings(this);
    settings->setWindowFlag(Qt::Dialog);
    settings->show();
}

void MainWindow::setToolBar(bool isExplorer){
    ui->actionEditer_titres->setEnabled(isExplorer);
    ui->actionRetour->setEnabled(isExplorer);
    ui->actionRecharger->setEnabled(isExplorer);
    ui->actionNouvel_album->setEnabled(isExplorer);

    ui->actionZoomIn->setEnabled(!isExplorer);
    ui->actionZoomOut->setEnabled(!isExplorer);
    ui->actionRestaurer->setEnabled(!isExplorer);
    ui->actionInfos->setEnabled(!isExplorer);
    ui->actionRogner->setEnabled(!isExplorer);
    ui->actionRedimensionner->setEnabled(!isExplorer);
    ui->actionRetour->setEnabled(!isExplorer);
    ui->actionEnregistrer->setEnabled(!isExplorer);
    ui->actionEnregistrer_sous->setEnabled(!isExplorer);
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
    //ajouter le bouton pour pouvoir ouvrir le Dock des images dans l'explorateur d'album dans lequel on ajoute les images.
    //A faire apres le refactor des UIs car c'est utile dans cette UI.
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
    visioToolBar->addAction(ui->actionRotationM);
    visioToolBar->addAction(ui->actionRotationP);

    visioToolBar->addSeparator();
    visioToolBar->addAction(ui->actionEnregistrer);
    visioToolBar->addAction(ui->actionEnregistrer_sous);
}
