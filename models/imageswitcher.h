#ifndef IMAGESWITCHER_H
#define IMAGESWITCHER_H


#include <QStandardItem>
#include <QStandardItemModel>
#include <QtDebug>
#include "models/image.h"

class ImageSwitcher
{
public:
    ImageSwitcher(QStandardItem *image, QStandardItemModel *model);
    Image getImage();

private:
    QStandardItem *m_image;
    QStandardItemModel *m_model;

public slots:
    Image imagePrecedente();
    Image imageSuivante();
};

#endif // IMAGESWITCHER_H
