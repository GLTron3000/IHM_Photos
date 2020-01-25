#include "visionneuse.h"
#include "ui_visionneuse.h"

#include <QLabel>
#include <QGridLayout>
#include <QDir>
#include <QStatusTipEvent>

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
    pixmap_img = new QPixmap(fileName);
    ui->image->setPixmap(*pixmap_img);

    const QString message = tr("Opened \"%1\", %2x%3, Depth: %4")
        .arg(QDir::toNativeSeparators(fileName)).arg(pixmap_img->width()).arg(pixmap_img->height()).arg(pixmap_img->depth());

    QCoreApplication::postEvent(this, new QStatusTipEvent(message));
}
