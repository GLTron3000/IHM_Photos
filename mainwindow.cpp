#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "widgets/settings.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
    ui->actionEnregistrer->setEnabled(false);
    ui->actionEnregistrer_sous->setEnabled(false);
    ui->actionRotationM->setEnabled(false);
    ui->actionRotationP->setEnabled(false);

    connect(ui->actionRetour, SIGNAL(triggered()), this, SLOT(showExplorer()));
    connect(ui->actionPr_f_rences, SIGNAL(triggered()), this, SLOT(showSettings()));

    connect(ui->actionQuitter, SIGNAL(triggered()), this, SLOT(quit()));
    connect(ui->actionPlein_cran, SIGNAL(triggered()), this, SLOT(fullscreen()));

    DataBase *db = new DataBase();
    db->cleaner();
    delete db;
    db = nullptr;

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
    ui->actionEnregistrer->setEnabled(true);
    ui->actionEnregistrer_sous->setEnabled(true);
    ui->actionRotationM->setEnabled(true);
    ui->actionRotationP->setEnabled(true);
}

void MainWindow::showExplorer(){
    qDebug() << "SHOW EXPLORER";

    explorer = new Explorer();
    connect(explorer, SIGNAL(openImageFromAlbum(ImageSwitcher*)), this, SLOT(showVisio(ImageSwitcher*)));
    this->setCentralWidget(explorer);

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
    ui->actionEnregistrer->setEnabled(false);
    ui->actionEnregistrer_sous->setEnabled(false);
    ui->actionRotationM->setEnabled(false);
    ui->actionRotationP->setEnabled(false);
}

void MainWindow::showSettings(){
    qDebug() << "SHOW SETTINGS";
    Settings *settings = new Settings(this);
    settings->setWindowFlag(Qt::Dialog);
    settings->show();
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
