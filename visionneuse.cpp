#include "visionneuse.h"
#include "ui_visionneuse.h"
#include "mainwindow.h"
#include "QInputDialog"
#include "widgets/resizeimgwidget.h"

#include <QLabel>
#include <QDir>
#include <QRect>
#include <QStatusTipEvent>
#include <QPixmap>
#include <QToolBar>
#include <QScrollArea>
#include <QGraphicsView>
#include <QDebug>
#include <QDockWidget>
#include <QTransform>

Visionneuse::Visionneuse(QWidget *parent, ImageSwitcher *imageSwitcher) :
    QMainWindow(parent),
    ui(new Ui::Visionneuse)
{
    ui->setupUi(this);
    this->imageSwitcher = imageSwitcher;

    scene = new QGraphicsScene();

    imagePixmap = new QGraphicsPixmapItem();

    graphicsViewZoom = new GraphicsViewZoom();
    graphicsViewZoom->setScene(scene);

    setCentralWidget(graphicsViewZoom);

    dock = new QDockWidget(this, Qt::Widget);
    this->addDockWidget(Qt::RightDockWidgetArea, dock);
    dock->setAllowedAreas(Qt::RightDockWidgetArea|Qt::LeftDockWidgetArea);
    dock->setVisible(false);

    toolbar = this->addToolBar(tr("visio"));

    toolbar->addAction(ui->actionRetour);
    toolbar->addSeparator();
    toolbar->addAction(ui->actionEnregistrer);
    toolbar->addAction(ui->actionEnregistrer_sous);
    toolbar->addSeparator();
    toolbar->addAction(ui->actionInfos);
    toolbar->addSeparator();
    toolbar->addAction(ui->actionImage_precedente);
    toolbar->addAction(ui->actionImage_suivante);
    toolbar->addSeparator();
    toolbar->addAction(ui->actionZoomIn);
    toolbar->addAction(ui->actionZoomOut);
    toolbar->addAction(ui->actionRetablir);
    toolbar->addSeparator();
    toolbar->addAction(ui->actionRotationM);
    toolbar->addAction(ui->actionRotationP);
    toolbar->addSeparator();
    toolbar->addAction(ui->actionRogner);
    toolbar->addAction(ui->actionRedimensionner);
    toolbar->addAction(ui->actionValider);
    toolbar->addSeparator();
    toolbar->addAction(ui->actionInfos);

    connect(ui->actionZoomIn, SIGNAL(triggered()), this, SLOT(zoomIn()));
    connect(ui->actionZoomOut, SIGNAL(triggered()), this, SLOT(zoomOut()));
    connect(ui->actionRetablir, SIGNAL(triggered()), this, SLOT(restaurerTailleImg()));
    connect(ui->actionRedimensionner, SIGNAL(triggered()), this, SLOT(resize()));
    connect(ui->actionRogner, SIGNAL(triggered()), this, SLOT(crop()));
    connect(ui->actionRotationM, SIGNAL(triggered()), this, SLOT(rotationPlus()));
    connect(ui->actionRotationP, SIGNAL(triggered()), this, SLOT(rotationMinus()));
    connect(ui->actionEnregistrer, SIGNAL(triggered()), this, SLOT(save()));
    connect(ui->actionEnregistrer_sous, SIGNAL(triggered()), this, SLOT(saveAs()));
    connect(ui->actionInfos, SIGNAL(triggered()), this, SLOT(afficherInformations()));
    connect(ui->actionRetour, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionValider, SIGNAL(triggered()), this, SLOT(setCrop()));

    connect(ui->actionImage_precedente, SIGNAL(triggered()), this, SLOT(imagePrecedente()));
    connect(ui->actionImage_suivante, SIGNAL(triggered()), this, SLOT(imageSuivante()));

}

Visionneuse::~Visionneuse()
{
    delete ui;
}

void Visionneuse::afficherInformations(){
    if(!visibleInfo){
        info = new Info(this, imagePath);
        dock->setWidget(info);
        dock->setVisible(true);
        visibleInfo = true;
    }else{
        visibleInfo = false;
        dock->setVisible(false);
        delete info;
        info = nullptr;
    }
}

void Visionneuse::afficherImage(QString path){   
    imagePath = path;

    graphicsViewZoom->scene()->removeItem(imagePixmap);

    imagePixmap = new QGraphicsPixmapItem(path);
    imagePixmap->setTransformationMode(Qt::SmoothTransformation);

    graphicsViewZoom->scene()->addItem(imagePixmap);
    graphicsViewZoom->initCrop();
    graphicsViewZoom->centerOn(imagePixmap);
}

void Visionneuse::zoomIn(){
    graphicsViewZoom->scaleAll(1.1);
}

void Visionneuse::zoomOut(){
    graphicsViewZoom->scaleAll(0.9);
}

void Visionneuse::restaurerTailleImg(){
    graphicsViewZoom->resetTransform();
    qDebug() << __FUNCTION__;
}

void Visionneuse::crop(){
    ui->actionValider->setEnabled(graphicsViewZoom->cropMode());
}

void Visionneuse::resize(){
    ResizeImgWidget *resizeImageWidget = new ResizeImgWidget(this, imagePixmap->pixmap().height(), imagePixmap->pixmap().width());
    connect(resizeImageWidget, SIGNAL(changeResolution(int, int)), this, SLOT(resizeTo(int, int)));
    resizeImageWidget->show();
}

void Visionneuse::resizeTo(int width, int height){
    qDebug() << "RESIZE h:" << height << " w:" << width;
    QImage image = imagePixmap->pixmap().toImage();
    QImage scaledImage = image.scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    graphicsViewZoom->scene()->removeItem(imagePixmap);

    imagePixmap = new QGraphicsPixmapItem(QPixmap::fromImage(scaledImage));

    graphicsViewZoom->scene()->addItem(imagePixmap);
}

void Visionneuse::createDockWindows(){
    info = new Info();
    this->setCentralWidget(info);
}

void Visionneuse::rotationPlus(){
    graphicsViewZoom->rotate(90);
}

void Visionneuse::rotationMinus(){
    graphicsViewZoom->rotate(-90);
}

void Visionneuse::save(){
    qDebug() << "SAVE";
    imagePixmap->pixmap().save(imagePath);
}

void Visionneuse::saveAs(){
    qDebug() << "SAVE AS";
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Sauvegarder image"), "",
            tr("Images (*)"));

    qDebug() << "   save location: " << fileName;

    graphicsViewZoom->grab(graphicsViewZoom->sceneRect().toRect()).save(fileName);
}

void Visionneuse::close(){
    emit closeVisio();
}

void Visionneuse::imagePrecedente(){
    graphicsViewZoom->resetTransform();
    afficherImage(imageSwitcher->imagePrecedente().path);
}

void Visionneuse::imageSuivante(){
    graphicsViewZoom->resetTransform();
    afficherImage(imageSwitcher->imageSuivante().path);
}

void Visionneuse::setCrop(){
    QPixmap cropPixmap = graphicsViewZoom->getRubberSelection();

    graphicsViewZoom->scene()->removeItem(imagePixmap);

    imagePixmap = new QGraphicsPixmapItem(cropPixmap);

    graphicsViewZoom->scene()->addItem(imagePixmap);
    crop();
    ui->actionRogner->setChecked(false);
    QApplication::restoreOverrideCursor();
}
