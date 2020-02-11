#include "resizeimgwidget.h"
#include "ui_resizeimgwidget.h"

ResizeImgWidget::ResizeImgWidget(QWidget *parent, int height, int width) :
    QWidget(parent),
    ui(new Ui::ResizeImgWidget)
{
    ui->setupUi(this);

    this->setWindowFlag(Qt::Dialog);
    this->setWindowTitle("Redimensionner");

    ratioH = (double)width/(double)height;
    ratioW = (double)height/(double)width;

    useRatio = false;
    signalBlock = false;

    ui->heightSpinBox->setValue(height);
    ui->widthSpinBox->setValue(width);

    connect(ui->heightSpinBox, SIGNAL(valueChanged(int)), this, SLOT(heightChange(int)));
    connect(ui->widthSpinBox, SIGNAL(valueChanged(int)), this, SLOT(widthChange(int)));
    connect(ui->checkBoxRatio, SIGNAL(stateChanged(int)), this, SLOT(checkRatio()));
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(abort()));
}

ResizeImgWidget::~ResizeImgWidget()
{
    delete ui;
}

//PRIVATE SLOTS
void ResizeImgWidget::accept(){
    width = ui->widthSpinBox->value();
    height = ui->heightSpinBox->value();

    emit changeResolution(width, height);
    this->close();
}

void ResizeImgWidget::abort(){
    this->close();
}

void ResizeImgWidget::checkRatio(){
    useRatio = ui->checkBoxRatio->isChecked();
}

void ResizeImgWidget::heightChange(int height){
    signalBlock = signalBlock ? false : true;
    if(signalBlock){
        return;
    }

    if(useRatio){
        ui->widthSpinBox->setValue(height * ratioH);
    }
}

void ResizeImgWidget::widthChange(int width){
    signalBlock = signalBlock ? false : true;
    if(signalBlock){
        return;
    }

    if(useRatio){
        ui->heightSpinBox->setValue(width * ratioW);
    }
}
