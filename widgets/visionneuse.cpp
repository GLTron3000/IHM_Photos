#include "visionneuse.h"
#include "ui_visionneuse.h"
#include "mainwindow.h"

#include <QLabel>
#include <QGridLayout>
#include <QDir>
#include <QStatusTipEvent>
#include <QPixmap>
#include <QToolBar>
#include <QScrollArea>

Visionneuse::Visionneuse(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Visionneuse)
{
    ui->setupUi(this);

    clipScene = new ClipScene(this, this->size());
    //clipScene->setRect();

    graphicsViewZoom = new GraphicsViewZoom();
    graphicsViewZoom->setScene(clipScene);
    setCentralWidget(graphicsViewZoom);
}

Visionneuse::~Visionneuse()
{
    qDebug() << "DESTRUCTOR 1";
    delete ui;
    qDebug() << "DESTRUCTOR 2";
    qDebug() << "DESTRUCTOR 3";
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

