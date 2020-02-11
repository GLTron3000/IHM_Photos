#ifndef SLIDESHOW_H
#define SLIDESHOW_H

#include <QMainWindow>
#include "models/imageswitcher.h"

namespace Ui {
class Slideshow;
}

class Slideshow : public QMainWindow
{
    Q_OBJECT

public:
    explicit Slideshow(QWidget *parent = nullptr, ImageSwitcher *imageSwitcher = NULL);
    ~Slideshow();

private slots:
    void nextImage();
    void prevImage();
    void quit();

private:
    Ui::Slideshow *ui;
    ImageSwitcher *imageSwitcher;

};

#endif // SLIDESHOW_H
