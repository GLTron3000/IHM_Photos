#include "exploreralbums.h"
#include "ui_exploreralbums.h"

#include <QtConcurrent/QtConcurrentRun>

ExplorerAlbums::ExplorerAlbums(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ExplorerAlbums)
{
    ui->setupUi(this);
    editMode = false;
    db = new DataBase();
    loadAlbums();

    ui->toolButtonAdd->setDefaultAction(ui->actionNouvel_album);
    ui->toolButtonDelete->setDefaultAction(ui->actionSupprimer_album);

    connect(ui->actionNouvel_album, SIGNAL(triggered()), this, SLOT(addAlbum()));
    connect(ui->actionSupprimer_album, SIGNAL(triggered()), this, SLOT(deleteAlbum()));
    connect(ui->listViewAlbums, SIGNAL(doubleClicked(const QModelIndex)), this, SLOT(onAlbumClick(QModelIndex)));
    connect(ui->listViewAlbums, SIGNAL(indexesMoved(const QModelIndexList)), this, SLOT(onAlbumMoved(QModelIndexList)));
    connect(ui->recherche, SIGNAL(textEdited(QString)), this, SLOT(searchList(QString)));

    //QtConcurrent::run(this, &DataBase::cleaner);
    db->cleaner();
}

ExplorerAlbums::~ExplorerAlbums()
{
    delete ui;
}

//PUBLIC SLOTS
void ExplorerAlbums::loadAlbums(){
    albumModel = db->getAlbums();

    //proxyModel = new QSortFilterProxyModel(this);
    //proxyModel->setSourceModel(albumModel);

    ui->listViewAlbums->setModel(albumModel);
}

void ExplorerAlbums::editTitle(){
    editMode = editMode ? false : true;
    qDebug() << "EDIT MODE " << editMode;
    ui->listViewAlbums->blockSignals(editMode);
}

void ExplorerAlbums::addAlbum(){
    QString albumName = QString("Album%1").arg(albumModel->rowCount());

    int id = db->addAlbum(albumName);

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

void ExplorerAlbums::searchList(QString name){
    qDebug() << "SEARCH : " << name;
    if(name == ""){
        qDebug() << "   +RESET";
        ui->listViewAlbums->setModel(albumModel);
        return;
    }

    albumSearchModel = new QStandardItemModel();
    for(int i=0; i < albumModel->rowCount(); i++){
        QStandardItem *album = albumModel->item(i);
        QString albumName = album->text();
        if(albumName.contains(name)){
            qDebug() << "   +=" << albumName;

            QStandardItem *item = new QStandardItem;
            item->setText(albumName);
            item->setData(album->data());
            item->setIcon(QIcon(":/ressources/images/defaultA.png"));
            albumSearchModel->appendRow(item);
        }
    }

    ui->listViewAlbums->setModel(albumSearchModel);
}

void ExplorerAlbums::deleteAlbum(){
    QModelIndexList indexes;
    qDebug() << "REMOVE ALBUM SELECTION";
    while((indexes = ui->listViewAlbums->selectionModel()->selectedIndexes()).size()) {
        qDebug() << "   +REMOVED ";
        int albumID = albumModel->item(indexes.first().row())->data().toInt();
        db->deleteAlbum(albumID);
        db->deleteAlbumImages(albumID);
        albumModel->removeRow(indexes.first().row());
    }
}
