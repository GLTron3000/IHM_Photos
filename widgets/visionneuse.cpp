#include "visionneuse.h"
#include "ui_visionneuse.h"
#include "mainwindow.h"

#include <QLabel>
#include <QGridLayout>
#include <QDir>
#include <QStatusTipEvent>
#include <QPixmap>
#include <QToolBar>

Visionneuse::Visionneuse(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Visionneuse)
{
    ui->setupUi(this);
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
    QLabel  *label = ui->image;

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
    label->setPixmap(pixmap_img->scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));


    const QString message = tr("Opened \"%1\", %2x%3, Depth: %4")
        .arg(QDir::toNativeSeparators(fileName)).arg(pixmap_img->width()).arg(pixmap_img->height()).arg(pixmap_img->depth());


    QCoreApplication::postEvent(this, new QStatusTipEvent(message));
}