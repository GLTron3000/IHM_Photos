#include "exploreralbimg.h"
#include "ui_exploreralbimg.h"

explorerAlbImg::explorerAlbImg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::explorerAlbImg)
{
    ui->setupUi(this);
}

explorerAlbImg::~explorerAlbImg()
{
    delete ui;
}
