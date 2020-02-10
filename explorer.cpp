#include "explorer.h"
#include "ui_explorer.h"

Explorer::Explorer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Explorer)
{
    ui->setupUi(this);
    showAlbums();
}

Explorer::~Explorer()
{
    delete ui;
}

void Explorer::showAlbums(){
    albums = new ExplorerAlbums();
    albumMode = true;

    connect(albums, SIGNAL(openAlbum(int)), this, SLOT(showAlbumImages(int)));

    setCentralWidget(albums);
}

void Explorer::showAlbumImages(int albumID){
    images = new ExplorerAblumImages();
    albumMode = false;
    currentAlbum = albumID;

    connect(images, SIGNAL(returnFromAlbum()), this, SLOT(showAlbums()));
    connect(images, SIGNAL(openImage(ImageSwitcher*)), this, SLOT(openImage(ImageSwitcher*)));

    images->loadImages(albumID);

    setCentralWidget(images);
}

void Explorer::openImage(ImageSwitcher *switcher){
    qDebug() << "EXPLORER SIGNAL" << switcher->getImage().path;
    emit openImageFromAlbum(switcher);
}

void Explorer::reload(){
    if(albumMode){
        albums->loadAlbums();
    }else{
        images->loadImages(currentAlbum);
    }
}
