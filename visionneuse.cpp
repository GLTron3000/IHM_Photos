#include "visionneuse.h"
#include "ui_visionneuse.h"

Visionneuse::Visionneuse(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Visionneuse)
{
    ui->setupUi(this);
}

Visionneuse::~Visionneuse()
{
    delete ui;
}
