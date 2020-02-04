#include "exploreralb.h"
#include "ui_exploreralb.h"

explorerAlb::explorerAlb(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::explorerAlb)
{
    ui->setupUi(this);
}

explorerAlb::~explorerAlb()
{
    delete ui;
}
