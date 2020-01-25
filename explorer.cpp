#include "explorer.h"
#include "ui_explorer.h"

#include <sstream>

#include <QDebug>
#include <QDirIterator>
#include <QPixmap>
#include <QStandardItem>
#include <QIcon>
#include <QtConcurrent/QtConcurrentRun>
#include <QStatusTipEvent>

Explorer::Explorer(QWidget *parent) :
    QWidget(parent)
    , ui(new Ui::Explorer)
{
    ui->setupUi(this);

    connect(ui->listViewImages, SIGNAL(clicked(const QModelIndex)), this, SLOT(onImageClick(QModelIndex)));
}

Explorer::~Explorer()
{
    delete ui;
}

void Explorer::loadImages(){
    imagesModel = new QStandardItemModel;
    //loadPath("/home/thomsb/Documents");
    loadPath("/home/thomsb/Images");
    loadPath("/mnt/DATA/Mes Images");
    ui->listViewImages->setModel(imagesModel);    

    QtConcurrent::run(this, &Explorer::loadThumbs);
}

void Explorer::loadPath(QString path){
    QDirIterator it(path, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        it.next();

        QString extension = it.fileInfo().suffix().toLower();
        if(extension == "png" || extension == "jpeg" || extension == "jpg"){
            QStandardItem *item = new QStandardItem;
            QString fileName = it.fileName().remove("."+it.fileInfo().suffix());
            item->setText(fileName);
            item->setData(it.filePath());
            imagesModel->appendRow(item);
        }
    }
}

void Explorer::loadThumbs(){
    for(int i=0; i < imagesModel->rowCount(); i++){
        QStandardItem *item =imagesModel->item(i,0);
        QVariant path = item->data();
        QImage *image = new QImage(path.toString());
        if(image->isNull()){
            item->setIcon(QIcon(":/ressources/images/default.png"));
        }else{
            item->setIcon(QIcon(QPixmap::fromImage(*image).scaledToWidth(200)));
        }
        delete image;
        image = nullptr;

        std::ostringstream oss;
        oss << i << "/" << imagesModel->rowCount();
        //QCoreApplication::postEvent(this, new QStatusTipEvent(QString::fromStdString(oss.str())));
    }
}

void Explorer::onImageClick(QModelIndex item){
    QStandardItem *image = imagesModel->itemFromIndex(item);
    qDebug() << image->data().toString();
    emit openImage(image->data().toString());
}


