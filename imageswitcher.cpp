#include "imageswitcher.h"

ImageSwitcher::ImageSwitcher(QStandardItem* image, QStandardItemModel* model)
{
    m_image = image;
    m_model = model;
}

void ImageSwitcher::imagePrecedente(){
    qDebug() << __FUNCTION__;
    m_image = m_model->item(m_image->row()-1);
}

void ImageSwitcher::imageSuivante(){
    qDebug() << __FUNCTION__;
    m_image = m_model->item(m_image->row()+1);
}
