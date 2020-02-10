#ifndef DATABASE_H
#define DATABASE_H
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QStandardItem>
#include "models/image.h"

class DataBase
{
public:
    DataBase();
    int addImageToAlbum(Image image, int position, int idAlbum);
    int addImage(QString path);
    int addAlbum(QString name);
    void addSource(QString path);
    void deleteImage(int id);
    void deleteImageFromAlbum(int albumId, int imageId);
    void deleteImageFromAll(int imageId);
    void deleteAlbumImages(int albumId);
    void deleteAlbum(int id);
    void deleteSource(int id);
    QStandardItemModel* getAlbums();
    QString getAlbumName(int id);
    QStandardItemModel* getImagesFromAlbum(int albumId);
    Image* getImageByPath(QString path);
    Image* getImageById(int id);
    QStringList* getSources();
    void updateAlbum(int id, QString name);
    void updateAlbumImage(int position, int idAlbum, int idImage);
    void updateImage(int id, QString path, int score, QString description, QString tags, QString feel);
    void cleaner();

public:
    QSqlDatabase m_db;

private:
    int getLastInsert();
};

#endif // DATABASE_H
