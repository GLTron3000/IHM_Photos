#include "editeurimage.h"
#include "ui_editeurimage.h"

#include "clipscene.h"
#include "QLabel"
#include "QPixmap"
#include "QImage"
#include "QGraphicsView"
#include "QtDebug"

EditeurImage::EditeurImage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditeurImage)
{
    ui->setupUi(this);
    m_graphicsView = ui->gView;
    m_clippedLabel = new QLabel();

    monImage = new QImage("/home/sim/Images/IMG_1919-3.jpg");

    ui->gView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->gView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_clipScene = new ClipScene(this, this->size());
    m_graphicsView->setScene(m_clipScene);
    m_clipScene->setImage("/home/sim/Images/IMG_1919-3.jpg");
    m_clipScene->setRect();

    connect(m_clipScene, &ClipScene::clippedImage, this, &EditeurImage::onClippedImage);

    //connect(ui->valider, &QPushButton::pressed, this, &MainWindow::cropImageAndSave);
}

EditeurImage::~EditeurImage()
{
    delete ui;
}


QSize EditeurImage::getSize(){
    return this->size();
}

void EditeurImage::cropImageAndSave(){

    QImage *image = new QImage();
    *image = m_clippedLabel->pixmap()->toImage();
    image->save("/home/sim/Images/wouatropbo.jpg");

}

void EditeurImage::onClippedImage(const QPixmap& pixmap)
{
    m_clippedLabel->setPixmap(pixmap);
}
