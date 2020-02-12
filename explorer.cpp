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

//PRIVATE SLOTS
void Explorer::showAlbums(){
    albums = new ExplorerAlbums();
    albumMode = true;

    connect(albums, SIGNAL(openAlbum(int)), this, SLOT(showAlbumImages(int)));

    setCentralWidget(albums);

    emit switchMenuBar(true);
}

void Explorer::showAlbumImages(int albumID){
    images = new ExplorerAblumImages();
    albumMode = false;
    currentAlbum = albumID;

    connect(images, SIGNAL(returnFromAlbum()), this, SLOT(showAlbums()));
    connect(images, SIGNAL(openImage(ImageSwitcher*)), this, SLOT(openImage(ImageSwitcher*)));

    images->loadImages(albumID);

    setCentralWidget(images);

    emit switchMenuBar(false);
}

void Explorer::openImage(ImageSwitcher *switcher){
    qDebug() << "EXPLORER SIGNAL" << switcher->getImage().path;
    emit openImageFromAlbum(switcher);
}


//PUBLIC SLOTS
void Explorer::reload(){
    if(albumMode){
        albums->loadAlbums();
    }else{
        images->loadImages(currentAlbum);
    }
}

void Explorer::newAlbum(){
    albums->addAlbum();
}

void Explorer::slideshow(){
    images->slideShow();
}

void Explorer::changeOrder(){
    images->reorderImage();
}

void Explorer::back(){
    showAlbums();
}

void Explorer::imageDrawer(){
    images->openImagesDrawer();
}

void Explorer::editTitle(){
    images->editTitle();
}
