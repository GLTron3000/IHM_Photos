#include "slideshow.h"
#include "ui_slideshow.h"

#include <QPixmap>
#include <QApplication>
#include <QScreen>

Slideshow::Slideshow(QWidget *parent, ImageSwitcher *imageSwitcher) :
    QMainWindow(parent),
    ui(new Ui::Slideshow)
{
    ui->setupUi(this);
    this->imageSwitcher = imageSwitcher;

    QRect rec = QGuiApplication::screens().first()->geometry();

    ui->label->setMaximumWidth(rec.width()-100);
    ui->label->setMaximumHeight(rec.height()-100);
    ui->label->setPixmap(imageSwitcher->getImage().path);

    ui->toolButtonNext->setDefaultAction(ui->actionImage_suivante);
    ui->toolButtonPrev->setDefaultAction(ui->actionImage_pr_c_dente);
    ui->toolButtonQuit->setDefaultAction(ui->actionQuitter);

    connect(ui->actionImage_suivante, SIGNAL(triggered()), this, SLOT(nextImage()));
    connect(ui->actionImage_pr_c_dente, SIGNAL(triggered()), this, SLOT(prevImage()));
    connect(ui->actionQuitter, SIGNAL(triggered()), this, SLOT(quit()));

    setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    setWindowState(Qt::WindowFullScreen);
    showFullScreen();
}

Slideshow::~Slideshow()
{
    delete ui;
}

void Slideshow::nextImage(){
   ui->label->setPixmap(imageSwitcher->imageSuivante().path);
}

void Slideshow::prevImage(){
    ui->label->setPixmap(imageSwitcher->imagePrecedente().path);
}

void Slideshow::quit(){
    this->close();
}
