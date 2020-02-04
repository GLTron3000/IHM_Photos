#include "info.h"
#include "ui_info.h"
#include <QInputDialog>
#include <QtDebug>
#include <QDockWidget>

Info::Info(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Info)
{
    ui->setupUi(this);
    ui->textElements->setReadOnly(true);
    ui->textFeelings->setReadOnly(true);
    ui->textKeyWords->setReadOnly(true);
    //ui->valueWHLabel->setNum(0);

    //const QString message = tr("Opened \"%1\", %2x%3").arg(QDir::toNativeSeparators(path)).arg(clipScene->width()).arg(clipScene->height());
       //QCoreApplication::postEvent(this, new QStatusTipEvent(message));

}

Info::~Info()
{
    delete ui;
}

void Info::setImgPath(QString imgpath){

    imgPath = imgpath;
}

void Info::setH(double height){
    imgHeight = height;
}

void Info::setW(double width){
    imgWidth = width;
}

void Info::setInfos(){
    QString wh = QString("%1 x %2").arg(imgWidth, imgHeight);
    //ui->valueWHLabel->setText(wh);

    ui->valueNameLabel->setText(imgPath);
}

void Info::on_ButtonEdit_clicked()
{
    modeEdition = modeEdition ? false : true;
    if(modeEdition){
        ui->ButtonEdit->setText("Sauvegarder");
        ui->textElements->setReadOnly(false);
        ui->textFeelings->setReadOnly(false);
        ui->textKeyWords->setReadOnly(false);
    }else{
        ui->ButtonEdit->setText("Modifier");
        ui->textElements->setReadOnly(true);
        ui->textFeelings->setReadOnly(true);
        ui->textKeyWords->setReadOnly(true);
    }

}

void Info::on_ButtonValider_clicked()
{

}
