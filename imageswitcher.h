#ifndef IMAGESWITCHER_H
#define IMAGESWITCHER_H


#include <QStandardItem>
#include <QStandardItemModel>
#include <QtDebug>

class ImageSwitcher
{
public:
    ImageSwitcher(QStandardItem *image, QStandardItemModel *model);
    QStandardItem *m_image;
    QStandardItemModel *m_model;

public slots:
    void imagePrecedente();
    void imageSuivante();
};

#endif // IMAGESWITCHER_H
