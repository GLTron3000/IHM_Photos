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
    setCentralWidget(ui->scrollAreaWidgetContents);

    QToolBar* toolbar = new QToolBar(this);
    toolbar->setMovable(false);
    toolbar->addAction(QIcon(":/ressources/images/default.png"), "Salut");
    toolbar->addAction(QIcon(":/ressources/images/INFO-01.png"), "reSalut");
}

Visionneuse::~Visionneuse()
{
    delete ui;
}

/*
 * TODO:
 *  Ajuster l'image a la fenêtre
 * */
void Visionneuse::afficherImage(QString fileName)
{
    label = ui->image;
    pixmap_img = new QPixmap(fileName);

    /*rotation____________
    QTransform t;
    QImage image;
    image.load(fileName);
    QImage img = image.transformed(t.rotate(90));
    QPixmap pix = QPixmap::fromImage(img);
       // display the pixmap on the label
       label->setPixmap(pix);
       */

    // set a scaled pixmap to a w x h window keeping its aspect ratio
    defaultSize = this->size();
    label->setPixmap(pixmap_img->scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));


    const QString message = tr("Opened \"%1\", %2x%3, Depth: %4")
        .arg(QDir::toNativeSeparators(fileName)).arg(pixmap_img->width()).arg(pixmap_img->height()).arg(pixmap_img->depth());


    QCoreApplication::postEvent(this, new QStatusTipEvent(message));
}

void Visionneuse::zoomIn(){
    qDebug() << __FUNCTION__;
    m_scaleFactor = 1;
    scaleImg(1.25);
}

void Visionneuse::zoomOut(){
    qDebug() << __FUNCTION__;
    m_scaleFactor = 1;
    scaleImg(0.75);
}

void Visionneuse::restaurerTailleImg(){
    qDebug() << __FUNCTION__;
    setDefaultSize();
}

void Visionneuse::setDefaultSize(){
    qDebug() << __FUNCTION__;
    label->setPixmap(pixmap_img->scaled(defaultSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void Visionneuse::scaleImg(double scaleFact)
{
    m_scaleFactor *= scaleFact;
    QSize newsize = label->pixmap()->size()*m_scaleFactor;
    label->setPixmap(pixmap_img->scaled(newsize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    const QString message = tr("Opened \"%1\", %2x%3, Depth: %4")
        .arg(QDir::toNativeSeparators("fileName")).arg(pixmap_img->width()).arg(pixmap_img->height()).arg(pixmap_img->depth());


    QCoreApplication::postEvent(this, new QStatusTipEvent(message));
}
