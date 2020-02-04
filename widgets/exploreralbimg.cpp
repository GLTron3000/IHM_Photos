#include "exploreralbimg.h"
#include "ui_exploreralbimg.h"

ExplorerAlbImg::ExplorerAlbImg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExplorerAlbImg)
{
    ui->setupUi(this);
    isImgVisible = false;
}

ExplorerAlbImg::~ExplorerAlbImg()
{
    delete ui;
}

void ExplorerAlbImg::afficherImg(){
    if(!isImgVisible){
        explImg = new ExplorerImg();
        isImgVisible = true;
        imgDock->setWidget(explImg);
        imgDock->setVisible(true);
    }else{
        isImgVisible = false;
        imgDock->setVisible(false);
        delete explImg;
        explImg = nullptr;
    }
}
