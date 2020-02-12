#include "info.h"
#include "ui_info.h"
#include <QInputDialog>
#include <QDebug>
#include <QDockWidget>
#include <QDirIterator>
#include <QStandardItem>
#include "database.h"
#include "stardelegate.h"
#include "starrating.h"

int numberOfStar;


Info::Info(QWidget *parent, QString imagePath) :
    QWidget(parent),
    ui(new Ui::Info)
{
    ui->setupUi(this);
    currentImgPath = imagePath;
    modeEdition = false;

    ui->textElements->setFrame(QFrame::StyledPanel);
    ui->textFeelings->setFrame(QFrame::StyledPanel);
    ui->textKeyWords->setFrame(QFrame::StyledPanel);

    QPalette p;
    p.setColor(QPalette::Base, QColor(240,240,240));
    ui->textElements->setPalette(p);
    ui->textFeelings->setPalette(p);
    ui->textKeyWords->setPalette(p);


    /* set le nom de l'image */
    QString deleteExtImg=imagePath.section(".",0,0);
    QString filename = deleteExtImg.section('/', -1);
    currentImgName = filename;

    /* set les dimensions de l'image */
    QString wString = QString::number(QImage(imagePath).width());
    QString hString = QString::number(QImage(imagePath).height());
    currentImgWxH = wString + " x " + hString;

    /* recup les infos de l'image qui sont dans la database */
    database = new DataBase();
    database->addImage(currentImgPath);
    currentImage = database->getImageByPath(currentImgPath);

    /* set les infos */
    ui->textElements->setText(currentImage->description);
    qDebug() <<currentImage->description;
    ui->textFeelings->setText(currentImage->feel);
    qDebug() <<currentImage->feel;
    ui->textKeyWords->setText(currentImage->tags);
    qDebug() <<currentImage->tags;

    /* set le système de notation */
    ui->note->setRowCount(1);
    ui->note->setColumnCount(1);
    ui->note->setItemDelegate(new StarDelegate);
    ui->note->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->note->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->note->horizontalHeader()->hide();
    ui->note->verticalHeader()->hide();

    int note = currentImage->score;
    struct {int rating;}
    Data[] = {{note}};
    item0 = new QTableWidgetItem;

    item0->setData(0,QVariant::fromValue(StarRating(Data[0].rating)));
    ui->note->setItem(0, 0, item0);
    ui->note->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->note->verticalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

    ui->note->setDisabled(true);

    /* set les zones de texte en lecture seulement */
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

        ui->textElements->setCursor(Qt::IBeamCursor);
        ui->textFeelings->setCursor(Qt::IBeamCursor);
        ui->textKeyWords->setCursor(Qt::IBeamCursor);
        ui->note->setCursor(Qt::PointingHandCursor);


        QPalette p;
        p.setColor(QPalette::Base, QColor(255,255,255));
        ui->textElements->setPalette(p);
        ui->textFeelings->setPalette(p);
        ui->textKeyWords->setPalette(p);

        ui->ButtonEdit->setText("Sauvegarder");
        ui->textElements->setReadOnly(false);
        ui->textFeelings->setReadOnly(false);
        ui->textKeyWords->setReadOnly(false);
        ui->note->setDisabled(false);

    }else{
        ui->textElements->setCursor(Qt::ArrowCursor);
        ui->textFeelings->setCursor(Qt::ArrowCursor);
        ui->textKeyWords->setCursor(Qt::ArrowCursor);
        ui->note->setCursor(Qt::ArrowCursor);
        ui->note->setDisabled(true);

        QPalette p;
        p.setColor(QPalette::Base, QColor(240,240,240));
        ui->textElements->setPalette(p);
        ui->textFeelings->setPalette(p);
        ui->textKeyWords->setPalette(p);

        ui->ButtonEdit->setText("Modifier");
        ui->textElements->setReadOnly(true);
        ui->textFeelings->setReadOnly(true);
        ui->textKeyWords->setReadOnly(true);

        database->updateImage(currentImage->id, currentImage->path, ::numberOfStar, ui->textElements->text(), ui->textKeyWords->text(), ui->textFeelings->text());

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
