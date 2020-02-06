#include "info.h"
#include "ui_info.h"
#include <QInputDialog>
#include <QDebug>
#include <QDockWidget>
#include <QDirIterator>
#include <QStandardItem>
#include "database.h"

Info::Info(QWidget *parent, QString imagePath) :
    QWidget(parent),
    ui(new Ui::Info)
{
    ui->setupUi(this);
    currentImgPath = imagePath;

    QImage imageQ = QImage(currentImgPath);



    QString deleteExtImg=imagePath.section(".",0,0);
    QString filename = deleteExtImg.section('/', -1);
    currentImgName = filename;

    QString wString = QString::number(QImage(imagePath).width());
    QString hString = QString::number(QImage(imagePath).height());
    currentImgWxH = wString + " x " + hString;

    DataBase *dataBase = new DataBase();
    dataBase->addImage(currentImgPath);
    Image *image = dataBase->getImageByPath(currentImgPath);

    ui->textElements->setText(image->description);
    ui->textFeelings->setText(image->tags);
    ui->textKeyWords->setText(image->tags);

    ui->textElements->setReadOnly(true);
    ui->textFeelings->setReadOnly(true);
    ui->textKeyWords->setReadOnly(true);
    ui->valueNameLabel->setText(currentImgName);
    ui->valueWHLabel->setText(currentImgWxH);
}

Info::~Info()
{
    delete ui;
}


void Info::on_ButtonEdit_clicked()
{
    modeEdition = modeEdition ? false : true;

    if(modeEdition){
        ui->ButtonEdit->setText("Sauvegarder");
        ui->textElements->setReadOnly(false);
        ui->textElements->setTextColor(QColor(0,0,0));
        ui->textFeelings->setReadOnly(false);
        ui->textElements->setTextColor(QColor(0,0,0));
        ui->textKeyWords->setReadOnly(false);
        ui->textElements->setTextColor(QColor(0,0,0));

    }else{
        ui->ButtonEdit->setText("Modifier");
        ui->textElements->setReadOnly(true);
        ui->textElements->setTextColor(QColor(169,169,169));
        //ui->textElements->setTextBackgroundColor(QColor(255, 0, 0));
        ui->textFeelings->setReadOnly(true);
        ui->textFeelings->setTextColor(QColor(169,169,169));
        ui->textKeyWords->setReadOnly(true);
        ui->textKeyWords->setTextColor(QColor(169,169,169));


    }

}

QColor dominantColour(const QImage& image,const QPoint& topLeft, const QSize& rectSize){
    const int maxRight = qMin(image.width(),topLeft.x() + rectSize.width());
    const int maxBottom = qMin(image.height(),topLeft.y() + rectSize.height());
    qint64 sumRed = 0;
    qint64 sumGreen = 0;
    qint64 sumBlue = 0;
    for(int x=topLeft.x();x<maxRight;++x){
        for(int y=topLeft.y();y<maxBottom;++y){
            const QColor tempColor=image.pixelColor(x,y);
            sumRed += tempColor.red();
            sumGreen += tempColor.green();
            sumBlue += tempColor.blue();
        }
    }
    if(sumRed >= sumGreen  && sumRed >= sumBlue)
        return Qt::red;
    if(sumGreen  >= sumBlue)
        return Qt::green;
    return Qt::blue;
}
