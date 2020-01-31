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
    int addImage(QString path, int position, int idAlbum);
    void deleteImage(int id);
    int addAlbum(QString name, int index);
    void deleteAlbum(int id);
    QStandardItemModel* getAlbums();
    QStandardItemModel* getImagesFromAlbum(int albumId);
    Image* getImageByPath(QString path);
    Image* getImageById(int id);
    void updateAlbum(int id, QString name, int index);
    void updateImage(int id, int index, int idAlbum);

public:
    QSqlDatabase m_db;

private:
    int getLastInsert();
};

#endif // DATABASE_H
