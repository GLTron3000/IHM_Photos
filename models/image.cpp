#include "image.h"

Image::Image(int id, QString path, QString description, QString tags, int score, QString feel)
{
    this->id = id;
    this->path = path;
    this->description = description;
    this->tags = tags;
    this->score = score;
    this->feel = feel;
}

void Image::initImage(){
    qRegisterMetaTypeStreamOperators<Image>("Image");
    qMetaTypeId<Image>();
}

QDataStream & operator << (QDataStream & out, const Image & Valeur)
{
    out << Valeur.path;

    return out;
}
QDataStream & operator >> (QDataStream & in, Image & Valeur)
{
    in >> Valeur.path;

    return in;
}

/*
Image::Image(){
    this->id = -1;
    this->path = "";
    this->description = "";
    this->tags = "";
    this->score = 0;
}
*/
