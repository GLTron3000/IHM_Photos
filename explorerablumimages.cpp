#include "explorerablumimages.h"
#include "ui_explorerablumimages.h"

#include <sstream>
#include <QInputDialog>
#include <QtConcurrent/QtConcurrentRun>
#include "slideshow.h"

ExplorerAblumImages::ExplorerAblumImages(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ExplorerAblumImages)
{
    ui->setupUi(this);
    albumID = -1;
    db = new DataBase();
    reorderMode = false;
    imgDock = new QDockWidget(this, Qt::Widget);
    this->addDockWidget(Qt::RightDockWidgetArea, imgDock);
    imgDock->createWinId();
    imgDock->setAllowedAreas(Qt::RightDockWidgetArea|Qt::LeftDockWidgetArea);
    imgDock->setVisible(false);

    ui->toolButtonClose->setDefaultAction(ui->actionRetour);
    ui->toolButtonOpenImages->setDefaultAction(ui->actionOpenImages);
    ui->toolButtonEditTitle->setDefaultAction(ui->actionEditer_le_titre);
    ui->toolButtonRemoveImage->setDefaultAction(ui->actionRetirer_l_image);
    ui->toolButtonReorder->setDefaultAction(ui->actionChangeImageOrder);
    ui->toolButtonSlide->setDefaultAction(ui->actionMode_diaporama);

    ui->listViewImages->setAcceptDrops(false);
    ui->listViewImages->setDropIndicatorShown(false);
    ui->listViewImages->setDragDropMode(QAbstractItemView::NoDragDrop);
    ui->listViewImages->setMovement(QListView::Static);

    connect(ui->actionRetour, SIGNAL(triggered()), this, SLOT(returnFrom()));
    connect(ui->actionOpenImages, SIGNAL(triggered()), this, SLOT(openImagesDrawer()));
    connect(ui->actionEditer_le_titre, SIGNAL(triggered()), this, SLOT(editTitle()));
    connect(ui->actionRetirer_l_image, SIGNAL(triggered()), this, SLOT(removeImage()));
    connect(ui->actionChangeImageOrder, SIGNAL(triggered()), this, SLOT(reorderImage()));
    connect(ui->actionMode_diaporama, SIGNAL(triggered()), this, SLOT(slideShow()));
    connect(ui->listViewImages, SIGNAL(doubleClicked(const QModelIndex)), this, SLOT(onImageClick(QModelIndex)));
    connect(imgDock, SIGNAL(visibilityChanged(bool)), this, SLOT(imageDrawerChange(bool)));

}

ExplorerAblumImages::~ExplorerAblumImages(){
    delete ui;
}

void ExplorerAblumImages::loadImages(int albumID){   
    albumImageModel = db->getImagesFromAlbum(albumID);
    this->albumTitle = db->getAlbumName(albumID);
    this->albumID = albumID;

    ui->labelTitre->setText(this->albumTitle);

    ui->listViewImages->setModel(albumImageModel);

    connect(this->albumImageModel, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(onAlbumImageModelChange(QStandardItem*)));
    QtConcurrent::run(this, &ExplorerAblumImages::loadThumbs, albumImageModel);
}


//PUBLIC SLOTS
void ExplorerAblumImages::reorderImage(){
    reorderMode = reorderMode ? false : true;
    if(reorderMode){
        ui->listViewImages->setViewMode(QListView::ListMode);
        ui->listViewImages->setDragDropMode(QAbstractItemView::InternalMove);
        ui->listViewImages->setMovement(QListView::Snap);

        ui->listViewImages->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->listViewImages->setDragEnabled(true);
        ui->listViewImages->viewport()->setAcceptDrops(true);
        ui->listViewImages->setDropIndicatorShown(true);
    }else{
        ui->listViewImages->setFlow(QListView::LeftToRight);
        ui->listViewImages->setViewMode(QListView::IconMode);
        ui->listViewImages->setDragDropMode(QAbstractItemView::NoDragDrop);
        ui->listViewImages->setMovement(QListView::Static);

        ui->listViewImages->setDragEnabled(false);
        ui->listViewImages->viewport()->setAcceptDrops(false);
        ui->listViewImages->setDropIndicatorShown(false);

        for(int i=0; i < albumImageModel->rowCount(); i++){
            qDebug() << " +" << i << " at " << albumImageModel->item(i)->text();
            db->updateAlbumImage(i, albumID, albumImageModel->item(i)->data().value<Image>().id);
        }
    }
}

void ExplorerAblumImages::slideShow(){
    ImageSwitcher *switcher = new ImageSwitcher(albumImageModel->item(0), albumImageModel);
    Slideshow *slideshow = new Slideshow(NULL, switcher);
    slideshow->show();
}

void ExplorerAblumImages::editTitle(){
    bool ok;
    QString text = QInputDialog::getText(this, tr("Modifier le titre de l'album"),
                                         tr("Titre de l'album:"), QLineEdit::Normal,
                                         albumTitle, &ok);
    if (ok && !text.isEmpty()){
        this->albumTitle = text;
        ui->labelTitre->setText(albumTitle);
        db->updateAlbum(albumID, albumTitle);
    }
}

void ExplorerAblumImages::openImagesDrawer(){
    imgDock->setVisible(imgDock->isVisible() ? false : true);
}


//PRIVATE
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


//PRIVATE SLOTS
void ExplorerAblumImages::returnFrom(){
    emit returnFromAlbum();
}

void ExplorerAblumImages::imageDrawerChange(bool visible){
    if(visible){
        qDebug() << "BUILD WIDGET";
        explImg = new ExplorerImg();
        imgDock->setWidget(explImg);
        connect(explImg, SIGNAL(openImage(ImageSwitcher*)), this, SLOT(openImageFromDrawer(ImageSwitcher*)));

        ui->actionOpenImages->setIcon(QIcon(":/ressources/images/CANCEL-01.png"));
        ui->actionOpenImages->setToolTip("Fermer le repertoire d'images");

        ui->listViewImages->setAcceptDrops(true);
        ui->listViewImages->setDropIndicatorShown(true);
        ui->listViewImages->setDragDropMode(QAbstractItemView::DropOnly);
    }else{
        qDebug() << "DESTROY WIDGET";
        //delete explImg;
        //explImg = nullptr;
        ui->actionOpenImages->setIcon(QIcon(":/ressources/images/NEWALBUM-02.png"));
        ui->actionOpenImages->setToolTip("Ouvrir le repertoire d'images");

        ui->listViewImages->setAcceptDrops(false);
        ui->listViewImages->setDropIndicatorShown(false);
        ui->listViewImages->setDragDropMode(QAbstractItemView::NoDragDrop);
    }
}

void ExplorerAblumImages::onImageClick(QModelIndex item){
    QStandardItem *image = albumImageModel->itemFromIndex(item);
    ImageSwitcher *switcher = new ImageSwitcher(image, albumImageModel);
    qDebug() << "Open Image " <<switcher->getImage().path;
    emit openImage(switcher);
}

void ExplorerAblumImages::onAlbumImageModelChange(QStandardItem *item){
    qDebug() << "ALBUM IMAGE MODEL CHANGE";
    if(item->text() == "") return;
    if(albumID == -1) return;
    qDebug() << "   +adding " << item->text() << " | " << item->data();
    QStandardItemModel *imageDb = db->getImagesFromAlbum(albumID);
    for(int i=0; i < imageDb->rowCount(); i++){
        if(imageDb->item(i)->data().value<Image>().path == item->data().value<Image>().path) return;
    }
    db->addImage(item->data().value<Image>().path);
    Image *image = db->getImageByPath(item->data().value<Image>().path);
    db->addImageToAlbum(*image, 0, albumID);
}

void ExplorerAblumImages::openImageFromDrawer(ImageSwitcher* switcher){
    emit openImage(switcher);
}

void ExplorerAblumImages::removeImage(){
    QModelIndexList indexes;
    qDebug() << "REMOVE SELECTION";
    while((indexes = ui->listViewImages->selectionModel()->selectedIndexes()).size()) {
        qDebug() << "   +REMOVED ";
        int imageID = albumImageModel->item(indexes.first().row())->data().value<Image>().id;
        db->deleteImageFromAlbum(albumID, imageID);
        albumImageModel->removeRow(indexes.first().row());
    }

    for(int i=0; i < albumImageModel->rowCount(); i++){
        int imageID = albumImageModel->item(i)->data().value<Image>().id;
        db->updateAlbumImage(i, albumID, imageID);
    }
}
