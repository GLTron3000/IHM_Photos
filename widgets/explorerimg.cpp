#include "explorerimg.h"
#include "ui_explorerimg.h"

#include "models/image.h"
#include <QDirIterator>
#include <sstream>
#include <QtConcurrent/QtConcurrentRun>

ExplorerImg::ExplorerImg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExplorerImg)
{
    ui->setupUi(this);
}

ExplorerImg::~ExplorerImg()
{
    delete ui;
}

void ExplorerImg::loadPath(QString path){
    QDirIterator it(path, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        it.next();

        QString extension = it.fileInfo().suffix().toLower();
        if(extension == "png" || extension == "jpeg" || extension == "jpg"){
            QStandardItem *item = new QStandardItem;
            QString fileName = it.fileName().remove("."+it.fileInfo().suffix());

            Image *image = new Image(-1, it.filePath(), "", "", 0);
            item->setText(fileName);
            item->setData(QVariant::fromValue(*image));
            imagesModel->appendRow(item);
        }
    }
}

void ExplorerImg::loadThumbs(QStandardItemModel *model){
    for(int i=0; i < model->rowCount(); i++){
        QStandardItem *item = model->item(i);
        QVariant path = item->data().value<Image>().path;
        QImage *image = new QImage(path.toString());
        if(image->isNull()){
            item->setIcon(QIcon(":/ressources/images/default.png"));
        }else{
            item->setIcon(QIcon(QPixmap::fromImage(*image).scaledToWidth(200)));
        }
        delete image;
        image = nullptr;

        std::ostringstream oss;
        oss << i << "/" << model->rowCount();
    }
}

//PUBLIC SLOTS
void ExplorerImg::loadImages(){
    imagesModel = new QStandardItemModel;

    QStringList *pathList = db->getSources();
    for (const auto& path : *pathList ){
        qDebug() << "LOADING SOURCE: " <<path;
        loadPath(path);
    }
    //loadPath(":/ressources");
    ui->listViewImages->setModel(imagesModel);
    if(thumbsLoader.isRunning()) thumbsLoader.cancel();
    thumbsLoader = QtConcurrent::run(this, &ExplorerImg::loadThumbs, imagesModel);
}
