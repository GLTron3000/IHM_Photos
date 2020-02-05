#include "explorerb.h"
#include "ui_explorerb.h"

ExplorerB::ExplorerB(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ExplorerB)
{
    ui->setupUi(this);
    showAlbums();
}

ExplorerB::~ExplorerB()
{
    delete ui;
}

void ExplorerB::showAlbums(){
    albums = new ExplorerAlbums();

    connect(albums, SIGNAL(openAlbum(int)), this, SLOT(showAlbumImages(int)));

    setCentralWidget(albums);
}

void ExplorerB::showAlbumImages(int albumID){
    images = new ExplorerAblumImages();

    connect(images, SIGNAL(returnFromAlbum()), this, SLOT(showAlbums()));

    images->loadImages(albumID);

    setCentralWidget(images);
}

