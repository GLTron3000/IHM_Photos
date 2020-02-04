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
    dock->createWinId();
    dock->setAllowedAreas(Qt::RightDockWidgetArea|Qt::LeftDockWidgetArea);

}

Visionneuse::~Visionneuse()
{
    delete ui;
}

void Visionneuse::afficherInformations(){
    if(!visibleInfo){
        info = new Info();

        info->setImgPath(imagePath);
        info->setH(clipScene->height());
        info->setW(clipScene->width());
        //info->setInfos(); /////////////////////::buguer la fenetre info

        dock->setWidget(info);
        dock->setVisible(true);
        visibleInfo = true;
    }else{
        visibleInfo = false;
        dock->setVisible(false);
        info = nullptr;
    }
}

void Visionneuse::afficherImage(QString path)
{   
    imagePath = path;
    imagePixmap = new QGraphicsPixmapItem(path);

    graphicsViewZoom->scene()->addItem(imagePixmap);
    graphicsViewZoom->initCrop();
}

void Visionneuse::zoomIn(){
    qDebug() << __FUNCTION__;
}

void Visionneuse::zoomOut(){
    qDebug() << __FUNCTION__;

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
    QPixmap cropPixmap = imagePixmap->pixmap().copy(graphicsViewZoom->rubber->geometry());
    cropPixmap.save(imagePath);
}

void Visionneuse::saveAs(){
    qDebug() << "SAVE AS MODS";
    QPixmap cropPixmap = imagePixmap->pixmap().copy(graphicsViewZoom->rubber->geometry());

    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Sauvegarder image"), "",
            tr("Images (*)"));

    qDebug() << "   save location: " << fileName;
    cropPixmap.save(fileName);
}
