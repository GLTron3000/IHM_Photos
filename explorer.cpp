#include "explorer.h"
#include "ui_explorer.h"

#include <QDebug>
#include <QDirIterator>
#include <QPixmap>
#include <QJsonObject>
#include <QStandardItem>
#include <QBrush>
#include <QIcon>
#include <QMovie>
#include <QtConcurrent/QtConcurrentRun>

Explorer::Explorer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Explorer)
{
    ui->setupUi(this);

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
}

void Explorer::loadPath(QString path){
    QDirIterator it(path, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        it.next();

        QString extension = it.fileInfo().suffix().toLower();
        qDebug() << "PATH " << it.path();
        qDebug() << "EXT " << extension;
        ;
        if(extension == "png" || extension == "jpeg" || extension == "jpg"){
            qDebug() << "ADDING";
            QStandardItem *item = new QStandardItem;
            QString fileName = it.fileName().remove("."+it.fileInfo().suffix());
            item->setText(fileName);
            item->setData(it.filePath());
            imagesModel->appendRow(item);
        }
    }

    QtConcurrent::run(this, &Explorer::loadThumbs);
}

void Explorer::loadThumbs(){
    for(int i=0; i < imagesModel->rowCount(); i++){
        QStandardItem *item =imagesModel->item(i,0);
        QVariant path = item->data();
        QImage *image = new QImage(path.toString());
        item->setIcon(QIcon(QPixmap::fromImage(*image).scaledToWidth(200)));

        delete image;
        image = nullptr;
    }
}
