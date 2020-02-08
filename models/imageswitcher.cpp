#include "imageswitcher.h"

ImageSwitcher::ImageSwitcher(QStandardItem* image, QStandardItemModel* model)
{
    m_image = image;
    m_model = model;
}

Image ImageSwitcher::getImage(){
    return m_image->data().value<Image>();
}


Image ImageSwitcher::imagePrecedente(){
    if(m_image->row() <= 0) m_image = m_model->item(m_model->rowCount()-1);
    else m_image = m_model->item(m_image->row()-1);
    return getImage();
}

Image ImageSwitcher::imageSuivante(){
    if(m_image->row() >= m_model->rowCount()-1) m_image = m_model->item(0);
    else m_image = m_model->item(m_image->row()+1);
    return getImage();
}
