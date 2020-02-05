#include "explorerablumimages.h"
#include "ui_explorerablumimages.h"

#include <sstream>
#include <QtConcurrent/QtConcurrentRun>

ExplorerAblumImages::ExplorerAblumImages(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ExplorerAblumImages)
{
    ui->setupUi(this);
    albumID = -1;
    db = new DataBase();
    imgDock = new QDockWidget(this, Qt::Widget);
    this->addDockWidget(Qt::RightDockWidgetArea, imgDock);
    imgDock->createWinId();
    imgDock->setAllowedAreas(Qt::RightDockWidgetArea|Qt::LeftDockWidgetArea);
    imgDock->setVisible(false);

    ui->toolButtonClose->setDefaultAction(ui->actionRetour);
    ui->toolButtonOpenImages->setDefaultAction(ui->actionOpenImages);

    ui->listViewImages->setAcceptDrops(true);
    ui->listViewImages->setDropIndicatorShown(true);
    ui->listViewImages->setDragDropMode(QAbstractItemView::DragDrop);

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

void ExplorerAblumImages::onAlbumImageModelChange(QStandardItem *item){
    qDebug() << "ALBUM IMAGE MODEL CHANGE";
    if(albumID == -1) return;
    qDebug() << "   +adding " << item->text() << " | " << item->data();
    QStandardItemModel *imageDb = db->getImagesFromAlbum(albumID);
    for(int i=0; i < imageDb->rowCount(); i++){
        if(imageDb->item(i)->data().value<Image>().path == item->data().value<Image>().path) return;
    }
    db->addImage(item->data().value<Image>().path, 0, albumID);
}

void ExplorerAblumImages::loadImages(int albumID){ 
    albumImageModel = db->getImagesFromAlbum(albumID);

    QString albumName = db->getAlbumName(albumID);
    ui->labelTitre->setText(albumName);

    ui->listViewImages->setModel(albumImageModel);

    this->albumID = albumID;
    connect(this->albumImageModel, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(onAlbumImageModelChange(QStandardItem*)));
    QtConcurrent::run(this, &ExplorerAblumImages::loadThumbs, albumImageModel);
}

void ExplorerAblumImages::openImagesDrawer(){
    if(imgDock->isVisible()){
        imgDock->setVisible(false);
        delete explImg;
        explImg = nullptr;
    }else{
        explImg = new ExplorerImg();
        imgDock->setWidget(explImg);
        imgDock->setVisible(true);
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
