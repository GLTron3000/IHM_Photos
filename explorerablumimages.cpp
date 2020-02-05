#include "explorerablumimages.h"
#include "ui_explorerablumimages.h"

#include <sstream>
#include <QtConcurrent/QtConcurrentRun>

ExplorerAblumImages::ExplorerAblumImages(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ExplorerAblumImages)
{
    ui->setupUi(this);
    db = new DataBase();
    isImgVisible = false;

    ui->toolButtonClose->setDefaultAction(ui->actionRetour);
    ui->toolButtonOpenImages->setDefaultAction(ui->actionOpenImages);

    connect(ui->actionRetour, SIGNAL(triggered()), this, SLOT(returnFrom()));
    connect(ui->actionOpenImages, SIGNAL(triggered()), this, SLOT(openImagesDrawer()));
    connect(ui->listViewImages, SIGNAL(doubleClicked(const QModelIndex)), this, SLOT(onImageClick(QModelIndex)));
}

ExplorerAblumImages::~ExplorerAblumImages()
{
    delete ui;
}

void ExplorerAblumImages::returnFrom(){
    emit returnFromAlbum();
}

void ExplorerAblumImages::loadImages(int albumID){
    albumImageModel = db->getImagesFromAlbum(albumID);

    QString albumName = db->getAlbumName(albumID);
    ui->labelTitre->setText(albumName);

    ui->listViewImages->setModel(albumImageModel);
    QtConcurrent::run(this, &ExplorerAblumImages::loadThumbs, albumImageModel);
}

void ExplorerAblumImages::openImagesDrawer(){
    if(!isImgVisible){
        explImg = new ExplorerImg();
        isImgVisible = true;
        imgDock->setWidget(explImg);
        imgDock->setVisible(true);
    }else{
        isImgVisible = false;
        imgDock->setVisible(false);
        delete explImg;
        explImg = nullptr;
    }
}

void ExplorerAblumImages::loadThumbs(QStandardItemModel *model){
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

void ExplorerAblumImages::onImageClick(QModelIndex item){
    QStandardItem *image = albumImageModel->itemFromIndex(item);
    qDebug() << "Open Image " <<image->data().value<Image>().path;
    emit openImage(image->data().value<Image>());
}
