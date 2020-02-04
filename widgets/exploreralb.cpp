#include "exploreralb.h"
#include "ui_exploreralb.h"

ExplorerAlb::ExplorerAlb(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExplorerAlb)
{
    ui->setupUi(this);
}

ExplorerAlb::~ExplorerAlb()
{
    delete ui;
}
