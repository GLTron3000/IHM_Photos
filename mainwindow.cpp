#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "widgets/settings.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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

void MainWindow::showVisio(QString path){
    qDebug() << "SHOW VISIO";
    visionneuse = new Visionneuse();
    visionneuse->afficherImage(path);

    explorerToolBar->hide();
    visioToolBar->show();

    connect(ui->actionZoomIn, SIGNAL(triggered()), visionneuse, SLOT(zoomIn()));
    connect(ui->actionZoomOut, SIGNAL(triggered()), visionneuse, SLOT(zoomOut()));
    connect(ui->actionRestaurer, SIGNAL(triggered()), visionneuse, SLOT(restaurerTailleImg()));
    connect(ui->actionRedimensionner, SIGNAL(triggered()), visionneuse, SLOT(resize()));
    connect(ui->actionRogner, SIGNAL(triggered()), visionneuse, SLOT(crop()));
    connect(ui->actionRotationM, SIGNAL(triggered()), visionneuse, SLOT(rotationPlus()));
    connect(ui->actionRotationP, SIGNAL(triggered()), visionneuse, SLOT(rotationMinus()));
    connect(ui->actionEnregistrer, SIGNAL(triggered()), visionneuse, SLOT(save()));
    connect(ui->actionEnregistrer_sous, SIGNAL(triggered()), visionneuse, SLOT(saveAs()));
    connect(ui->actionInfos, SIGNAL(triggered()), visionneuse, SLOT(informations()));

    this->setCentralWidget(visionneuse);
    setToolBar(false);
}

void MainWindow::showExplorer(){
    qDebug() << "SHOW EXPLORER";
    explorer = new Explorer();
    explorer->loadImages();

    visioToolBar->hide();
    explorerToolBar->show();

    connect(explorer, SIGNAL(openImage(QString)), this, SLOT(showVisio(QString)));
    connect(ui->actionNouvel_album, SIGNAL(triggered()), explorer, SLOT(addAlbum()));
    connect(ui->actionRecharger, SIGNAL(triggered()), explorer, SLOT(loadImages()));
    connect(ui->actionEditer_titres, SIGNAL(triggered()), explorer, SLOT(editTitle()));
    connect(ui->actionRetour_Album, SIGNAL(triggered()), explorer, SLOT(returnAlbum()));

    this->setCentralWidget(explorer);
    setToolBar(true);
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
