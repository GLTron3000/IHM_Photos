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

    /*ui->textElements->cursor().setShape(Qt::ArrowCursor);
    ui->textFeelings->cursor().setShape(Qt::ArrowCursor);
    ui->textElements->cursor().setShape(Qt::ArrowCursor);*/

    ui->textElements->setFrameShape(QFrame::NoFrame);
    ui->textFeelings->setFrameShape(QFrame::NoFrame);
    ui->textKeyWords->setFrameShape(QFrame::NoFrame);

    /*QPalette p;
    p.setColor(QPalette::Base, QColor(250,250,250));
    ui->textElements->setPalette(p);
    ui->textFeelings->setPalette(p);
    ui->textKeyWords->setPalette(p);*/

    ui->textElements->setTextColor(QColor(169,169,169));
    ui->textFeelings->setTextColor(QColor(169,169,169));
    ui->textKeyWords->setTextColor(QColor(169,169,169));

    QString deleteExtImg=imagePath.section(".",0,0);
    QString filename = deleteExtImg.section('/', -1);
    currentImgName = filename;

    QString wString = QString::number(QImage(imagePath).width());
    QString hString = QString::number(QImage(imagePath).height());
    currentImgWxH = wString + " x " + hString;

    database = new DataBase();
    database->addImage(currentImgPath);
    currentImage = database->getImageByPath(currentImgPath);


    ui->textElements->setText(currentImage->description);
    ui->textFeelings->setText(currentImage->tags);
    ui->textKeyWords->setText(currentImage->tags);

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
        ui->textElements->cursor().setShape(Qt::IBeamCursor);
        ui->textFeelings->setCursor(Qt::IBeamCursor);
        ui->textKeyWords->setCursor(Qt::IBeamCursor);

        ui->textElements->setFrameShape(QFrame::StyledPanel);
        ui->textFeelings->setFrameShape(QFrame::StyledPanel);
        ui->textKeyWords->setFrameShape(QFrame::StyledPanel);

        /*QPalette p;
        p.setColor(QPalette::Base, QColor(255,255,255)); // set color "Red" for textedit base
        ui->textElements->setPalette(p); // change textedit palette
        ui->textFeelings->setPalette(p);
        ui->textKeyWords->setPalette(p);*/

        ui->ButtonEdit->setText("Sauvegarder");
        ui->textElements->setReadOnly(false);
        ui->textElements->setTextColor(QColor(0,0,0));
        ui->textElements->update();
        ui->textFeelings->setReadOnly(false);
        ui->textElements->setTextColor(QColor(0,0,0));
        ui->textKeyWords->setReadOnly(false);
        ui->textElements->setTextColor(QColor(0,0,0));

    }else{
        ui->textElements->cursor().setShape(Qt::ArrowCursor);
        ui->textFeelings->cursor().setShape(Qt::ArrowCursor);
        ui->textKeyWords->cursor().setShape(Qt::ArrowCursor);

        ui->textElements->setFrameShape(QFrame::NoFrame);
        ui->textFeelings->setFrameShape(QFrame::NoFrame);
        ui->textKeyWords->setFrameShape(QFrame::NoFrame);

        /*QPalette p;
        p.setColor(QPalette::Base, QColor(250,250,250));
        ui->textElements->setPalette(p);
        ui->textFeelings->setPalette(p);
        ui->textKeyWords->setPalette(p);*/

        ui->ButtonEdit->setText("Modifier");
        ui->textElements->setReadOnly(true);
        ui->textElements->setTextColor(QColor(169,169,169));
        ui->textFeelings->setReadOnly(true);
        ui->textFeelings->setTextColor(QColor(169,169,169));
        ui->textKeyWords->setReadOnly(true);
        ui->textKeyWords->setTextColor(QColor(169,169,169));

        database->updateImage(currentImage->id, currentImage->path, 5, ui->textElements->toPlainText(), ui->textKeyWords->toPlainText());
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
