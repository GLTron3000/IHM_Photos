#include "explorer.h"
#include "ui_explorer.h"

#include <QDebug>
#include <QDirIterator>
#include <QPixmap>
#include <QJsonObject>
#include <QStandardItem>
#include <QBrush>
#include <QIcon>

Explorer::Explorer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Explorer)
{
    ui->setupUi(this);
    loadFiles();
}

Explorer::~Explorer()
{
    delete ui;
}

void Explorer::loadFiles(){
    QDirIterator it("/home/thomsb/Images", QDirIterator::Subdirectories);
    model = new QStandardItemModel;
    while (it.hasNext()) {
        QImage *image = new QImage(it.next());
        if(!image->isNull()){
            QStandardItem *item = new QStandardItem;
            item->setIcon(QIcon(QPixmap::fromImage(*image).scaledToWidth(200)));

            QString fileName = it.fileName();

            fileName.remove("."+it.fileInfo().suffix());

            if(fileName.length() > 15){
                fileName.resize(15);
                fileName.append("...");
            }

            item->setText(fileName);
            item->setData(it.path());
            model->appendRow(item);
        }
    }
    ui->listViewImages->setModel(model);
}
