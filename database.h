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
    int addAlbum(QString name, int index);
    void addSource(QString path);
    void deleteImage(int id);
    void deleteAlbum(int id);
    int deleteSource(QString path);
    QStandardItemModel* getAlbums();
    QString getAlbumName(int id);
    QStandardItemModel* getImagesFromAlbum(int albumId);
    Image* getImageByPath(QString path);
    Image* getImageById(int id);
    QStringList* getSources();
    void updateAlbum(int id, QString name, int index);
    void updateImage(int id, int index, int idAlbum);

public:
    QSqlDatabase m_db;

private:
    int getLastInsert();
};

#endif // DATABASE_H
