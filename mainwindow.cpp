#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/ressources/images/LOGO2.png"));

    connect(ui->actionPr_f_rences, SIGNAL(triggered()), this, SLOT(showSettings()));
    connect(ui->actionA_propos, SIGNAL(triggered()), this, SLOT(showAbout()));
    connect(ui->actionAide_en_ligne, SIGNAL(triggered()), this, SLOT(showHelp()));

    connect(ui->actionQuitter, SIGNAL(triggered()), this, SLOT(quit()));
    connect(ui->actionPlein_cran, SIGNAL(triggered()), this, SLOT(fullscreen()));

    DataBase *db = new DataBase();
    db->cleaner();
    delete db;
    db = nullptr;

    about = NULL;
    settings = NULL;

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

    connect(ui->actionZoomIn, SIGNAL(triggered()), visionneuse, SLOT(zoomIn()));
    connect(ui->actionZoomOut, SIGNAL(triggered()), visionneuse, SLOT(zoomOut()));
    connect(ui->actionRetablir, SIGNAL(triggered()), visionneuse, SLOT(restaurerTailleImg()));
    connect(ui->actionInfos, SIGNAL(triggered()), visionneuse, SLOT(afficherInformations()));
    connect(ui->actionRogner, SIGNAL(triggered()), visionneuse, SLOT(crop()));
    connect(ui->actionRedimensionner, SIGNAL(triggered()), visionneuse, SLOT(resize()));
    connect(ui->actionEnregistrer, SIGNAL(triggered()), visionneuse, SLOT(save()));
    connect(ui->actionEnregistrer_sous, SIGNAL(triggered()), visionneuse, SLOT(saveAs()));
    connect(ui->actionRotationM, SIGNAL(triggered()), visionneuse, SLOT(rotationMinus()));
    connect(ui->actionRotationP, SIGNAL(triggered()), visionneuse, SLOT(rotationPlus()));
    connect(ui->actionImageSuivante, SIGNAL(triggered()), visionneuse, SLOT(imageSuivante()));
    connect(ui->actionImagePrecedente, SIGNAL(triggered()), visionneuse, SLOT(imagePrecedente()));


    this->setCentralWidget(visionneuse);

    setMenuVisionneuse();
}

void MainWindow::showExplorer(){
    qDebug() << "SHOW EXPLORER";

    explorer = new Explorer();
    connect(explorer, SIGNAL(openImageFromAlbum(ImageSwitcher*)), this, SLOT(showVisio(ImageSwitcher*)));
    connect(explorer, SIGNAL(switchMenuBar(bool)), this, SLOT(switchExplorer(bool)));

    connect(ui->actionActualiser, SIGNAL(triggered()), explorer, SLOT(reload()));
    connect(ui->actionDiaporama, SIGNAL(triggered()), explorer, SLOT(slideshow()));
    connect(ui->actionChangerOrder, SIGNAL(triggered()), explorer, SLOT(changeOrder()));
    connect(ui->actionTiroirImages, SIGNAL(triggered()), explorer, SLOT(imageDrawer()));
    connect(ui->actionRetour, SIGNAL(triggered()), explorer, SLOT(back()));
    connect(ui->actionEditer, SIGNAL(triggered()), explorer, SLOT(editTitle()));
    connect(ui->actionNouvel_album, SIGNAL(triggered()), explorer, SLOT(newAlbum()));

    this->setCentralWidget(explorer);

    setMenuAlbums();
}

void MainWindow::showSettings(){
    qDebug() << "SHOW SETTINGS";
    if(settings != NULL) settings->close();
    settings = new Settings(this);
    settings->setWindowFlag(Qt::Dialog);
    settings->show();
}

void MainWindow::showAbout(){
    qDebug() << "SHOW ABOUT";
    if(about != NULL) about->close();
    about = new About(this);
    about->setWindowFlag(Qt::Dialog);
    about->show();
}

void MainWindow::showHelp(){
    QString link = "https://github.com/GLTron3000/IHM_Photos";
    QDesktopServices::openUrl(QUrl(link));
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

void MainWindow::keyPressEvent(QKeyEvent *ev){
    qDebug() << ev->text() << "Appuye";
    switch (ev->key()) {
        case Qt::Key_Escape :
            if(this->isFullScreen()) this->showNormal();
        break;
    }
}

void MainWindow::switchExplorer(bool isAlbums){
    if(isAlbums) setMenuAlbums();
    else setMenuAlbumImages();
}

void MainWindow::setMenuAlbums(){
    ui->actionActualiser->setEnabled(true);

    ui->actionNouvel_album->setEnabled(true);

    ui->actionRetour->setEnabled(false);
    ui->actionEditer->setEnabled(false);
    ui->actionTiroirImages->setEnabled(false);
    ui->actionChangerOrder->setEnabled(false);
    ui->actionDiaporama->setEnabled(false);

    ui->actionZoomIn->setEnabled(false);
    ui->actionZoomOut->setEnabled(false);
    ui->actionRetablir->setEnabled(false);
    ui->actionInfos->setEnabled(false);
    ui->actionRogner->setEnabled(false);
    ui->actionRedimensionner->setEnabled(false);
    ui->actionEnregistrer->setEnabled(false);
    ui->actionEnregistrer_sous->setEnabled(false);
    ui->actionRotationM->setEnabled(false);
    ui->actionRotationP->setEnabled(false);
    ui->actionImageSuivante->setEnabled(false);
    ui->actionImagePrecedente->setEnabled(false);
}

void MainWindow::setMenuAlbumImages(){
    ui->actionActualiser->setEnabled(true);

    ui->actionNouvel_album->setEnabled(false);

    ui->actionRetour->setEnabled(true);
    ui->actionEditer->setEnabled(true);
    ui->actionTiroirImages->setEnabled(true);
    ui->actionChangerOrder->setEnabled(true);
    ui->actionDiaporama->setEnabled(true);

    ui->actionZoomIn->setEnabled(false);
    ui->actionZoomOut->setEnabled(false);
    ui->actionRetablir->setEnabled(false);
    ui->actionInfos->setEnabled(false);
    ui->actionRogner->setEnabled(false);
    ui->actionRedimensionner->setEnabled(false);
    ui->actionEnregistrer->setEnabled(false);
    ui->actionEnregistrer_sous->setEnabled(false);
    ui->actionRotationM->setEnabled(false);
    ui->actionRotationP->setEnabled(false);
    ui->actionImageSuivante->setEnabled(false);
    ui->actionImagePrecedente->setEnabled(false);
}

void MainWindow::setMenuVisionneuse(){
    ui->actionActualiser->setEnabled(false);

    ui->actionNouvel_album->setEnabled(false);

    ui->actionRetour->setEnabled(false);
    ui->actionEditer->setEnabled(false);
    ui->actionTiroirImages->setEnabled(false);
    ui->actionChangerOrder->setEnabled(false);
    ui->actionDiaporama->setEnabled(false);

    ui->actionZoomIn->setEnabled(true);
    ui->actionZoomOut->setEnabled(true);
    ui->actionRetablir->setEnabled(true);
    ui->actionInfos->setEnabled(true);
    ui->actionRogner->setEnabled(true);
    ui->actionRedimensionner->setEnabled(true);
    ui->actionEnregistrer->setEnabled(true);
    ui->actionEnregistrer_sous->setEnabled(true);
    ui->actionRotationM->setEnabled(true);
    ui->actionRotationP->setEnabled(true);
    ui->actionImageSuivante->setEnabled(true);
    ui->actionImagePrecedente->setEnabled(true);
}
