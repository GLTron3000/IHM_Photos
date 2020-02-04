#include "visionneuse.h"
#include "ui_visionneuse.h"
#include "mainwindow.h"
#include "QInputDialog"

#include <QLabel>
#include <QDir>
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

    clipScene = new ClipScene(this, this->size());
    //clipScene->setRect(); // <----------- !! crash instant !! effectivement

    graphicsViewZoom = new GraphicsViewZoom();
    graphicsViewZoom->setScene(clipScene);
    graphicsViewZoom->setDragMode(QGraphicsView::ScrollHandDrag);
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
    clipScene->setImage(path);

   //const QString message = tr("Opened \"%1\", %2x%3").arg(QDir::toNativeSeparators(path)).arg(clipScene->width()).arg(clipScene->height());
   //QCoreApplication::postEvent(this, new QStatusTipEvent(message));
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
    if(editMode == EditMode::crop){
        editMode = EditMode::none;
        graphicsViewZoom->setDragMode(QGraphicsView::ScrollHandDrag);
    }else{
        editMode = EditMode::crop;
        graphicsViewZoom->setDragMode(QGraphicsView::RubberBandDrag);
        graphicsViewZoom->setRubberBandSelectionMode(Qt::ContainsItemBoundingRect);
    }
}

void Visionneuse::resize(){

}

void Visionneuse::createDockWindows(){
    info = new Info();
    this->setCentralWidget(info);
}

