#include "editeurimage.h"
#include "ui_editeurimage.h"

EditeurImage::EditeurImage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditeurImage)
{
    ui->setupUi(this);
}

EditeurImage::~EditeurImage()
{
    delete ui;
}
