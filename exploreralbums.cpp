#include "exploreralbums.h"
#include "ui_exploreralbums.h"

ExplorerAlbums::ExplorerAlbums(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ExplorerAlbums)
{
    ui->setupUi(this);
    editMode = false;
    db = new DataBase();
    loadAlbums();

    ui->toolButton->setDefaultAction(ui->actionNouvel_album);
    connect(ui->actionNouvel_album, SIGNAL(triggered()), this, SLOT(addAlbum()));

    connect(ui->listViewAlbums, SIGNAL(doubleClicked(const QModelIndex)), this, SLOT(onAlbumClick(QModelIndex)));
    connect(ui->listViewAlbums, SIGNAL(indexesMoved(const QModelIndexList)), this, SLOT(onAlbumMoved(QModelIndexList)));
}

ExplorerAlbums::~ExplorerAlbums()
{
    delete ui;
}

//PUBLIC SLOTS
void ExplorerAlbums::loadAlbums(){
    albumModel = db->getAlbums();
    ui->listViewAlbums->setModel(albumModel);
}

void ExplorerAlbums::editTitle(){
    editMode = editMode ? false : true;
    qDebug() << "EDIT MODE " << editMode;
    ui->listViewAlbums->blockSignals(editMode);
}

void ExplorerAlbums::addAlbum(){
    QString albumName = QString("Album%1").arg(albumModel->rowCount());

    int id = db->addAlbum(albumName, albumModel->rowCount());

    QStandardItem *item = new QStandardItem;
    item->setIcon(QIcon(":/ressources/images/defaultA.png"));
    item->setText(albumName);
    item->setData(id);
    albumModel->appendRow(item);
}


//PRIVATE SLOTS
void ExplorerAlbums::onAlbumClick(QModelIndex item){
    QStandardItem *album = albumModel->itemFromIndex(item);
    int albumID = album->data().toInt();
    qDebug() << "Open Album " << albumID;

    emit openAlbum(albumID);
}

void ExplorerAlbums::onAlbumMoved(QModelIndexList indexes){
    qDebug() << "ALBUMS MOVED";
    for(int i=0; i < indexes.count(); i++){
        qDebug() << indexes.at(i).column();
        qDebug() << albumModel->itemFromIndex(indexes.at(i))->row();
    }
}
