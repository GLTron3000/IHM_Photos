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
#include <QLayout>
#include <QTabBar>
#include <QToolBar>
#include <QMenu>
#include "models/image.h"

Explorer::Explorer(QWidget *parent) :
    QWidget(parent)
    , ui(new Ui::Explorer)
{
    ui->setupUi(this);

    QListView *listViewImages = ui->listViewImages;
    listViewImages->setSelectionMode(QAbstractItemView::ExtendedSelection);
    listViewImages->setDragEnabled(true);
    listViewImages->setAcceptDrops(false);
    listViewImages->setDropIndicatorShown(false);

    QListView *listViewAlbum = ui->listViewAlbum;
    listViewAlbum->setSelectionMode(QAbstractItemView::ExtendedSelection);
    listViewAlbum->setDragEnabled(true);

    db = new DataBase();
    currentAlbum = -1;
    editMode = false;
    moveMode = false;
    loadAlbums();

    connect(ui->listViewImages, SIGNAL(doubleClicked(const QModelIndex)), this, SLOT(onImageClick(QModelIndex)));
    connect(ui->listViewAlbum, SIGNAL(doubleClicked(const QModelIndex)), this, SLOT(onAlbumClick(QModelIndex)));
    connect(this->albumModel, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(onAlbumModelChange(QStandardItem*)));
    //connect(this->albumImageModel, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(onAlbumImageModelChange(QStandardItem*)));
    connect(ui->listViewAlbum, SIGNAL(indexesMoved(const QModelIndexList)), this, SLOT(onAlbumMoved(QModelIndexList)));
}

Explorer::~Explorer()
{
    delete ui;
    thumbsLoader.cancel();
}

void Explorer::loadPath(QString path){
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

void Explorer::loadThumbs(QStandardItemModel *model){
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




//PRIVATE SLOTS
void Explorer::onImageClick(QModelIndex item){
    QStandardItem *image = imagesModel->itemFromIndex(item);
    qDebug() << "Open Image " <<image->data().value<Image>().path;
    emit openImage(image->data().value<Image>().path);
}

void Explorer::onAlbumClick(QModelIndex item){
    QStandardItem *album = albumModel->itemFromIndex(item);
    int albumID = album->data().toInt();
    qDebug() << "Open Album " << albumID;

    currentAlbum = albumID;
    albumImageModel = db->getImagesFromAlbum(albumID);

    ui->listViewAlbum->setModel(albumImageModel);
    ui->listViewAlbum->setAcceptDrops(true);
    ui->listViewAlbum->setDropIndicatorShown(true);
    ui->listViewAlbum->setDragDropMode(QAbstractItemView::DragDrop);

    connect(this->albumImageModel, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(onAlbumImageModelChange(QStandardItem*)));

    QtConcurrent::run(this, &Explorer::loadThumbs, albumImageModel);
}

void Explorer::onAlbumModelChange(QStandardItem *item){
    //db update album item.text() with id  !!!  cpt   !!!
    qDebug() << "ALBUM MODEL CHANGE " << item->text() << " | " << item->data();

    db->updateAlbum(item->data().toInt(), item->text(), 0);
}

void Explorer::onAlbumImageModelChange(QStandardItem *item){
    qDebug() << "ALBUM IMAGE MODEL CHANGE";
    qDebug() << "ALBUM IMAGE MODEL CHANGE " << item->text() << " | " << item->data();
    if(currentAlbum == -1) return;
    QStandardItemModel *imageDb = db->getImagesFromAlbum(currentAlbum);
    for(int i=0; i < imageDb->rowCount(); i++){
        if(imageDb->item(i)->data().value<Image>().path == item->data().value<Image>().path) return;
    }
    db->addImage(item->data().value<Image>().path, 0, currentAlbum);
}

void Explorer::onAlbumMoved(QModelIndexList indexes){
    qDebug() << "ALBUMS MOVED";
    for(int i=0; i < indexes.count(); i++){
        qDebug() << indexes.at(i).column();
        qDebug() << albumModel->itemFromIndex(indexes.at(i))->row();
    }
}




//PUBLIC SLOTS
void Explorer::loadAlbums(){
    albumModel = db->getAlbums();
    albumImageModel = new QStandardItemModel;

    ui->listViewAlbum->setModel(albumModel);
}

void Explorer::loadImages(){
    imagesModel = new QStandardItemModel;

    QStringList *pathList = db->getSources();
    for (const auto& path : *pathList ){
        qDebug() << "LOADING SOURCE: " <<path;
        loadPath(path);
    }
    //loadPath(":/ressources");
    ui->listViewImages->setModel(imagesModel);
    if(thumbsLoader.isRunning()) thumbsLoader.cancel();
    thumbsLoader = QtConcurrent::run(this, &Explorer::loadThumbs, imagesModel);
}

void Explorer::editTitle(){
    editMode = editMode ? false : true;
    qDebug() << "EDIT MODE " << editMode;
    ui->listViewAlbum->blockSignals(editMode);
    ui->listViewImages->blockSignals(editMode);
}

void Explorer::addAlbum(){
    QString albumName = QString("Album%1").arg(albumModel->rowCount());

    int id = db->addAlbum(albumName, albumModel->rowCount());

    QStandardItem *item = new QStandardItem;
    item->setIcon(QIcon(":/ressources/images/defaultA.png"));
    item->setText(albumName);
    item->setData(id);
    albumModel->appendRow(item);
}

void Explorer::returnAlbum(){
    currentAlbum = -1;
    ui->listViewAlbum->setModel(albumModel);
    ui->listViewAlbum->setAcceptDrops(false);
    ui->listViewAlbum->setDropIndicatorShown(false);
    ui->listViewAlbum->setDragDropMode(QAbstractItemView::InternalMove);
}











