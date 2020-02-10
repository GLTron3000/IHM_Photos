#include "explorerablumimages.h"
#include "ui_explorerablumimages.h"

#include <sstream>
#include <QInputDialog>
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
    ui->toolButtonEditTitle->setDefaultAction(ui->actionEditer_le_titre);
    ui->toolButtonRemoveImage->setDefaultAction(ui->actionRetirer_l_image);

    ui->listViewImages->setAcceptDrops(true);
    ui->listViewImages->setDropIndicatorShown(true);
    ui->listViewImages->setDragDropMode(QAbstractItemView::DragDrop);

    connect(ui->actionRetour, SIGNAL(triggered()), this, SLOT(returnFrom()));
    connect(ui->actionOpenImages, SIGNAL(triggered()), this, SLOT(openImagesDrawer()));
    connect(ui->actionEditer_le_titre, SIGNAL(triggered()), this, SLOT(editTitle()));
    connect(ui->actionRetirer_l_image, SIGNAL(triggered()), this, SLOT(removeImage()));
    connect(ui->listViewImages, SIGNAL(doubleClicked(const QModelIndex)), this, SLOT(onImageClick(QModelIndex)));
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

void ExplorerAblumImages::openImagesDrawer(){
    if(imgDock->isVisible()){
        imgDock->setVisible(false);
        delete explImg;
        explImg = nullptr;
        //ui->actionOpenImages->setIcon(QIcon(":/ressources/images/NEWALBUM-02.png"));
        ui->actionOpenImages->setToolTip("Ouvrir le repertoire d'images");
    }else{
        explImg = new ExplorerImg();
        imgDock->setWidget(explImg);
        imgDock->setVisible(true);
        //ui->actionOpenImages->setIcon(QIcon(":/ressources/images/ok.png"));
        ui->actionOpenImages->setToolTip("Fermer le repertoire d'images");
        connect(explImg, SIGNAL(openImage(ImageSwitcher*)), this, SLOT(openImageFromDrawer(ImageSwitcher*)));
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






