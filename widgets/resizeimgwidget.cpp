#include "resizeimgwidget.h"
#include "ui_resizeimgwidget.h"

ResizeImgWidget::ResizeImgWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResizeImgWidget)
{
    ui->setupUi(this);
}

ResizeImgWidget::~ResizeImgWidget()
{
    delete ui;
}
