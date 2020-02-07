#ifndef IMAGE_H
#define IMAGE_H

#include <QMetaType>
#include <iostream>
#include <QString>

class Image
{
public:
    Image() = default;
    ~Image() = default;
    Image(const Image &) = default;
    Image &operator=(const Image &) = default;

    Image(int id, QString path, QString description, QString tags, int score, QString feel);
    int id;
    QString path;
    int score;
    QString description;
    QString tags;
    QString feel;
    static void initImage ();

private:
    friend QDataStream & operator << (QDataStream &, const Image &);
    friend QDataStream & operator >> (QDataStream &, Image &);
};
Q_DECLARE_METATYPE(Image);
QDataStream & operator << (QDataStream & out, const Image & Valeur);
QDataStream & operator >> (QDataStream & in, Image & Valeur);


#endif // IMAGE_H
