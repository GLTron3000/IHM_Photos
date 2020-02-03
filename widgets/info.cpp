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

    //ui->

}

Info::~Info()
{
    delete ui;
}

void Info::setImgPath(QString imgpath){
    imgPath = imgpath;
}

void Info::on_ButtonEdit_clicked()
{

}

void Info::on_ButtonValider_clicked()
{

}
