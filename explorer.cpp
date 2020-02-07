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

    connect(albums, SIGNAL(openAlbum(int)), this, SLOT(showAlbumImages(int)));

    setCentralWidget(albums);
}

void Explorer::showAlbumImages(int albumID){
    images = new ExplorerAblumImages();

    connect(images, SIGNAL(returnFromAlbum()), this, SLOT(showAlbums()));
    connect(images, SIGNAL(openImage(Image)), this, SLOT(openImage(Image)));

    images->loadImages(albumID);

    setCentralWidget(images);
}

void Explorer::openImage(Image image){
    qDebug() << "EXPLORERB SIGNAL" << image.path;
    emit openImageFromAlbum(image);
}
