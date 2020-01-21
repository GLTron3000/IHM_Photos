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

    connect(ui->actionRecharger, SIGNAL(triggered()), this, SLOT(reload()));
    connect(ui->actionQuitter, SIGNAL(triggered()), this, SLOT(quit()));
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
    }
}

void Explorer::reload(){
    loadImages();
}

void Explorer::quit(){
    QApplication::quit();
}
