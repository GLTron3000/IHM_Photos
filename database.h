#ifndef DATABASE_H
#define DATABASE_H
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QStandardItem>

class DataBase
{
public:
    DataBase();
    void addImg(QString path, int idAlbum);
    void deleteImg(int id);
    void addAlbum(QString name, int index);
    void deleteAlbum(int id);
    QStandardItemModel* getAlbum();
    QStandardItemModel* getImage(int albumId);
    void updateAlbum(int id, QString name, int index);
    void updateImage(int id, int index, int idAlbum);

public:
    QSqlDatabase m_db;

};

#endif // DATABASE_H
