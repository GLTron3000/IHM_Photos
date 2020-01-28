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

Explorer::Explorer(QWidget *parent) :
    QWidget(parent)
    , ui(new Ui::Explorer)
{
    ui->setupUi(this);
    loadAlbums();

    QToolBar* toolbar = new QToolBar(ui->frame);
    toolbar->addAction(QIcon(":/ressources/images/default.png"), "Salut");

    QVBoxLayout* layoutToolBar = new QVBoxLayout(this);
    layoutToolBar->addWidget(toolbar);

    connect(ui->listViewImages, SIGNAL(clicked(const QModelIndex)), this, SLOT(onImageClick(QModelIndex)));
    connect(ui->listViewImages, SIGNAL(doubleClicked(const QModelIndex)), this, SLOT(onAlbumClick(QModelIndex)));
    connect(ui->listViewAlbum, SIGNAL(doubleClicked(const QModelIndex)), this, SLOT(onImageClick(QModelIndex)));
    connect(ui->refreshButton, SIGNAL(clicked()), this, SLOT(onRefreshClick()));
    connect(ui->albumAddButton, SIGNAL(clicked()), this, SLOT(onAlbumAddClick()));
    connect(this->albumModel, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(onAlbumModelChange(QStandardItem*)));

    QListView *listViewImages = ui->listViewImages;
    listViewImages->setSelectionMode(QAbstractItemView::ExtendedSelection);
    listViewImages->setDragEnabled(true);
    listViewImages->setAcceptDrops(false);
    listViewImages->setDropIndicatorShown(false);

    QListView *listViewAlbum = ui->listViewAlbum;
    listViewAlbum->setSelectionMode(QAbstractItemView::ExtendedSelection);
    listViewAlbum->setDragEnabled(true);
    listViewAlbum->setAcceptDrops(true);
    listViewAlbum->setDropIndicatorShown(true);
//    QToolBar* toolbar = new QToolBar(this);

//    toolbar->addAction("Coucou");
//    toolbar->addAction("Salut");
//    QVBoxLayout* layout = new QVBoxLayout();
//    layout->setMenuBar(toolbar);
//    QTabBar *tabBar = new QTabBar(this);
//    tabBar->addTab("Object Graph");
//    tabBar->addTab("Snapshot #1");
//    tabBar->setObjectName("another_tab");
//    tabBar->setMinimumHeight(300);
//    layout->addWidget(tabBar, 0, Qt::AlignTop);
//    layout->setMargin(0);
//    layout->setContentsMargins(0, 0,0,0);
//    layout->setSpacing(0);
//    setLayout(layout);
}

Explorer::~Explorer()
{
    delete ui;
}

void Explorer::loadAlbums(){
    albumModel = new QStandardItemModel;
    ui->listViewAlbum->setModel(albumModel);
}

void Explorer::loadImages(){
    imagesModel = new QStandardItemModel;
    loadPath("/amuhome/f16016927");
//    loadPath("/home/sim/Images");
//    loadPath("/mnt/DATA/Mes Images");
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

void Explorer::onAlbumClick(QModelIndex item){

}

void Explorer::onRefreshClick(){
    loadImages();
}
void Explorer::onAlbumAddClick(){
    //get last index
    //add to db
    //get from db
    QStandardItem *item = new QStandardItem;
    item->setIcon(QIcon(":/ressources/images/default.png"));
    item->setText("Album");
    item->setData("id");
    albumModel->appendRow(item);
}

void Explorer::onAlbumModelChange(QStandardItem *item){
    int id = item->data().toInt();
    //db update item.text() with id
    qDebug() << "ALBUM MODEL CHANGE" <<id << " | " << item->text();
}
