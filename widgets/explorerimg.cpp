#include "explorerimg.h"
#include "ui_explorerimg.h"

ExplorerImg::ExplorerImg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExplorerImg)
{
    ui->setupUi(this);
}

ExplorerImg::~ExplorerImg()
{
    delete ui;
}
