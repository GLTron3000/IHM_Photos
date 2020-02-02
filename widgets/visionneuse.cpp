#include "visionneuse.h"
#include "ui_visionneuse.h"
#include "mainwindow.h"
#include "QInputDialog"

#include <QLabel>
#include <QGridLayout>
#include <QDir>
#include <QStatusTipEvent>
#include <QPixmap>
#include <QToolBar>
#include <QScrollArea>
#include <QGraphicsView>
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
    createDockWindows();
}

Visionneuse::~Visionneuse()
{
    delete ui;
}

void Visionneuse::createDockWindows(){
    QDockWidget *dock = new QDockWidget(tr("Informations"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea);

    QStringList infos = {"Nom :","", "Dimensions :"};
    QPushButton *modifierTags = new QPushButton("Modifier tags", this);
    QPushButton *modifierFeelings = new QPushButton("Modifier feelings", this);

    QHBoxLayout * layout = new QHBoxLayout;
    layout->addWidget(modifierTags);
    //layout->addWidget(modifierFeelings);

    labelList = new QListWidget(dock);
    labelList->addItems(infos);
    //buttonList->addItems();
    dock->setWidget(labelList);
    dock->setLayout(layout);
    addDockWidget(Qt::RightDockWidgetArea, dock);
        /*viewMenu->addAction(dock->toggleViewAction());*/


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

