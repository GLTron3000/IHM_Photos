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
    modeEdition = false;

    ui->textElements->setFrameShape(QFrame::StyledPanel);
    ui->textFeelings->setFrameShape(QFrame::StyledPanel);
    ui->textKeyWords->setFrameShape(QFrame::StyledPanel);

    QPalette p;
    p.setColor(QPalette::Base, QColor(240,240,240));
    ui->textElements->setPalette(p);
    ui->textFeelings->setPalette(p);
    ui->textKeyWords->setPalette(p);

    QString deleteExtImg=imagePath.section(".",0,0);
    QString filename = deleteExtImg.section('/', -1);
    currentImgName = filename;

    QString wString = QString::number(QImage(imagePath).width());
    QString hString = QString::number(QImage(imagePath).height());
    currentImgWxH = wString + " x " + hString;

    database = new DataBase();
    database->addImage(currentImgPath);//////////////////////////////////////////////
    currentImage = database->getImageByPath(currentImgPath);


    ui->textElements->setText(currentImage->description);
    qDebug() <<currentImage->description;
    ui->textFeelings->setText(currentImage->feel);
    qDebug() <<currentImage->feel;
    ui->textKeyWords->setText(currentImage->tags);
    qDebug() <<currentImage->tags;

    ui->textElements->setReadOnly(true);
    ui->textFeelings->setReadOnly(true);
    ui->textKeyWords->setReadOnly(true);
    ui->valueNameLabel->setText(currentImgName);
    ui->valueWHLabel->setText(currentImgWxH);

    QImage *qimage = new QImage(currentImgPath);
    QColor color;
    QPoint tl = qimage->rect().topLeft();
    const int maxRight = qMin(qimage->width(),tl.x() + qimage->width());
    const int maxBottom = qMin(qimage->height(),tl.y() + qimage->height());
    qint64 sumRed = 0;
    qint64 sumGreen = 0;
    qint64 sumBlue = 0;
    for(int x=tl.x();x<maxRight;++x){
        for(int y=tl.y();y<maxBottom;++y){
            const QColor tempColor=qimage->pixelColor(x,y);
            sumRed += tempColor.red();
            sumGreen += tempColor.green();
            sumBlue += tempColor.blue();
        }
    }
    if(sumRed >= sumGreen  && sumRed >= sumBlue)
        color =  Qt::red;
    else if(sumGreen  >= sumBlue)
        color =  Qt::green;
    else
        color = Qt::blue;

    ui->FrameColor->setPalette(QPalette(color));
}

Info::~Info()
{
    delete ui;
}


void Info::on_ButtonEdit_clicked()
{
    modeEdition = modeEdition ? false : true;

    if(modeEdition){

        ui->textElements->viewport()->setCursor(Qt::IBeamCursor);
        ui->textFeelings->viewport()->setCursor(Qt::IBeamCursor);
        ui->textKeyWords->viewport()->setCursor(Qt::IBeamCursor);

        QPalette p;
        p.setColor(QPalette::Base, QColor(255,255,255));
        ui->textElements->setPalette(p);
        ui->textFeelings->setPalette(p);
        ui->textKeyWords->setPalette(p);

        ui->ButtonEdit->setText("Sauvegarder");
        ui->textElements->setReadOnly(false);
        ui->textFeelings->setReadOnly(false);
        ui->textKeyWords->setReadOnly(false);

    }else{
        ui->textElements->viewport()->setCursor(Qt::ArrowCursor);
        ui->textFeelings->viewport()->setCursor(Qt::ArrowCursor);
        ui->textKeyWords->viewport()->setCursor(Qt::ArrowCursor);

        QPalette p;
        p.setColor(QPalette::Base, QColor(240,240,240));
        ui->textElements->setPalette(p);
        ui->textFeelings->setPalette(p);
        ui->textKeyWords->setPalette(p);

        ui->ButtonEdit->setText("Modifier");
        ui->textElements->setReadOnly(true);
        ui->textFeelings->setReadOnly(true);
        ui->textKeyWords->setReadOnly(true);

        database->updateImage(currentImage->id, currentImage->path, 5, ui->textElements->toPlainText(), ui->textKeyWords->toPlainText(), ui->textFeelings->toPlainText());

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
