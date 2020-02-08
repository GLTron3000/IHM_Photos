#include "explorerimg.h"
#include "ui_explorerimg.h"

#include "models/image.h"
#include <QDirIterator>
#include <sstream>
#include <QtConcurrent/QtConcurrentRun>

ExplorerImg::ExplorerImg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExplorerImg)
{
    ui->setupUi(this);

    ui->listViewImages->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->listViewImages->setDragEnabled(true);
    ui->listViewImages->setAcceptDrops(false);
    ui->listViewImages->setDropIndicatorShown(false);

    connect(ui->recherche, SIGNAL(textEdited(QString)), this, SLOT(searchList(QString)));
    connect(ui->listViewImages, SIGNAL(doubleClicked(const QModelIndex)), this, SLOT(onImageClick(QModelIndex)));

    loadImages();
}

ExplorerImg::~ExplorerImg()
{
    delete ui;
}

void ExplorerImg::loadPath(QString path){
    QDirIterator it(path, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        it.next();

        QString extension = it.fileInfo().suffix().toLower();
        if(isSupportedFormat(extension)){
            QStandardItem *item = new QStandardItem;
            QString fileName = it.fileName().remove("."+it.fileInfo().suffix());

            Image *image = db->getImageByPath(it.filePath());
            item->setText(fileName);
            item->setData(QVariant::fromValue(*image));
            imagesModel->appendRow(item);
        }
    }
}

bool ExplorerImg::isSupportedFormat(QString format){
    return     format == "bmp"
            || format == "gif"
            || format == "jpg"
            || format == "jpeg"
            || format == "png"
            || format == "pbm"
            || format == "pgm"
            || format == "xbm"
            || format == "xpm";
}

void ExplorerImg::loadThumbs(QStandardItemModel *model){
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

//PUBLIC SLOTS
void ExplorerImg::loadImages(){
    imagesModel = new QStandardItemModel;

    QStringList *pathList = db->getSources();
    for (const auto& path : *pathList ){
        qDebug() << "LOADING SOURCE: " <<path;
        loadPath(path);
    }
    //loadPath(":/ressources");
    ui->listViewImages->setModel(imagesModel);
    if(thumbsLoader.isRunning()) thumbsLoader.cancel();
    thumbsLoader = QtConcurrent::run(this, &ExplorerImg::loadThumbs, imagesModel);
}

//PRIVATE SLOTS
void ExplorerImg::searchList(QString name){
    qDebug() << "SEARCH : " << name;
    if(name == ""){
        qDebug() << "   +RESET";
        ui->listViewImages->setModel(imagesModel);
        return;
    }

    imagesSearchModel = new QStandardItemModel();
    for(int i=0; i < imagesModel->rowCount(); i++){
        Image image = imagesModel->item(i)->data().value<Image>();
        QStringList parts = image.path.split("/");
        QString filename = parts.at(parts.size()-1);

        QString compareElement;
        QString filter = ui->rechercheFilter->currentText();

        if(filter == "Description") compareElement = image.description;
        else if(filter == "Tags") compareElement = image.tags;
        else if(filter == "Sentiment") compareElement = image.feel;
        else compareElement = filename;

        if(compareElement.contains(name.toLower())){
            qDebug() << "   +=" << filename;

            QStandardItem *item = new QStandardItem;

            item->setText(filename);
            item->setData(QVariant::fromValue(image));
            imagesSearchModel->appendRow(item);
        }
    }

    ui->listViewImages->setModel(imagesSearchModel);

    if(!thumbsLoader.isFinished()) thumbsLoader.cancel();
    thumbsLoader = QtConcurrent::run(this, &ExplorerImg::loadThumbs, imagesSearchModel);
}

void ExplorerImg::onImageClick(QModelIndex item){
    QStandardItem *image = imagesModel->itemFromIndex(item);
    ImageSwitcher *switcher = new ImageSwitcher(image, imagesModel);
    qDebug() << "Open Image " <<switcher->getImage().path;
    emit openImage(switcher);
}









