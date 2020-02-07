#include "visionneuse.h"
#include "ui_visionneuse.h"
#include "mainwindow.h"
#include "QInputDialog"

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

Visionneuse::Visionneuse(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Visionneuse)
{
    ui->setupUi(this);

    scene = new QGraphicsScene();

    graphicsViewZoom = new GraphicsViewZoom();
    graphicsViewZoom->setScene(scene);

    setCentralWidget(graphicsViewZoom);

    dock = new QDockWidget(this, Qt::Widget);
    this->addDockWidget(Qt::RightDockWidgetArea, dock);
    //dock->createWinId();
    dock->setAllowedAreas(Qt::RightDockWidgetArea|Qt::LeftDockWidgetArea);
    dock->setVisible(false);

    toolbar = this->addToolBar(tr("visio"));
    toolbar->addAction(ui->actionRetour);
    toolbar->addAction(ui->actionInfos);

    toolbar->addSeparator();
    toolbar->addAction(ui->actionZoomIn);
    toolbar->addAction(ui->actionZoomOut);
    toolbar->addAction(ui->actionRetablir);

    toolbar->addSeparator();
    toolbar->addAction(ui->actionRogner);
    toolbar->addAction(ui->actionRedimensionner);
    toolbar->addAction(ui->actionRotationM);
    toolbar->addAction(ui->actionRotationP);

    toolbar->addSeparator();
    toolbar->addAction(ui->actionEnregistrer);
    toolbar->addAction(ui->actionEnregistrer_sous);

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

void Visionneuse::afficherImage(QString path)
{   
    imagePath = path;
    imagePixmap = new QGraphicsPixmapItem(path);
    imagePixmap->setTransformationMode(Qt::SmoothTransformation);

    graphicsViewZoom->scene()->addItem(imagePixmap);
    graphicsViewZoom->initCrop(new ResizableRubberBand(this));
}

void Visionneuse::zoomIn(){
    qDebug() << __FUNCTION__;

    graphicsViewZoom->scaleAll(1.1);
}

void Visionneuse::zoomOut(){
    qDebug() << __FUNCTION__;

    graphicsViewZoom->scaleAll(0.9);
}

void Visionneuse::restaurerTailleImg(){
    qDebug() << __FUNCTION__;
}

void Visionneuse::crop(){
    graphicsViewZoom->cropMode();
}

void Visionneuse::resize(){

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
    qDebug() << "SAVE MODS";
    QPixmap cropPixmap = imagePixmap->pixmap().copy(graphicsViewZoom->rubberR->geometry());
    cropPixmap.save(imagePath);
}

void Visionneuse::saveAs(){
    qDebug() << "SAVE AS MODS";
    QPixmap cropPixmap = imagePixmap->pixmap().copy(graphicsViewZoom->rubberR->geometry());

    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Sauvegarder image"), "",
            tr("Images (*)"));

    qDebug() << "   save location: " << fileName;
    cropPixmap.save(fileName);
}

void Visionneuse::close(){
    emit closeVisio();
}
