#include "database.h"

DataBase::DataBase()
{
    const QString DRIVER("QSQLITE");
    if(!QSqlDatabase::isDriverAvailable(DRIVER)) qDebug() << "Driver not Available";

    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("/home/thomsb/testoDB.sqlite");
    if(!m_db.open()) qDebug() << "ERROR: " << m_db.lastError();
    else qDebug() << "Database ok";

    QSqlQuery query;
    if(!query.exec("CREATE TABLE IF NOT EXISTS albums (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT UNIQUE NOT NULL, position INTEGER UNIQUE NOT NULL)"))
        qDebug() << "ERROR create albums " << query.lastError();
    if(!query.exec("CREATE TABLE IF NOT EXISTS images (id INTEGER PRIMARY KEY AUTOINCREMENT, path TEXT UNIQUE NOT NULL, score INTEGER NOT NULL, description TEXT, tags TEXT)"))
        qDebug() << "ERROR create images " << query.lastError();
    if(!query.exec("CREATE TABLE IF NOT EXISTS albumImages (id INTEGER PRIMARY KEY AUTOINCREMENT, idImage INTEGER NOT NULL, idAlbum INTEGER NOT NULL, position INTEGER NOT NULL)"))
        qDebug() << "ERROR create albumImages " << query.lastError();

    if(!query.exec("CREATE TABLE IF NOT EXISTS sources (id INTEGER PRIMARY KEY AUTOINCREMENT, path TEXT NOT NULL)"))
        qDebug() << "ERROR create sources " << query.lastError();
    if(!query.exec("CREATE TABLE IF NOT EXISTS settings (id INTEGER PRIMARY KEY AUTOINCREMENT, key TEXT UNIQUE NOT NULL, path TEXT NOT NULL)"))
        qDebug() << "ERROR create settings " << query.lastError();

}

int DataBase::getLastInsert(){
    QSqlQuery query("SELECT last_insert_rowid()");
    query.exec();

    return query.lastInsertId().toInt();
}

int DataBase::addImage(QString path, int position, int idAlbum){
    qDebug() << "Add image :" << path << " | i:" << position << " | idA:" << idAlbum;
    QSqlQuery query;

    query.prepare("INSERT INTO images (path, score, description, tags) VALUES(?,?,?,?)");
    query.addBindValue(path);
    query.addBindValue(0);
    query.addBindValue("");
    query.addBindValue("");
    if(!query.exec()){
        qDebug() << "ERROR add image: " << query.lastError();
    }

    QStandardItemModel *albumImages = getImagesFromAlbum(idAlbum);
    Image *image = getImageByPath(path);
    int albumPosition = albumImages->rowCount();

    query.prepare("INSERT INTO albumImages (idImage, idAlbum, position) VALUES(?,?,?)");
    query.addBindValue(image->id);
    query.addBindValue(idAlbum);
    query.addBindValue(albumPosition);
    if(!query.exec()){
        qDebug() << "ERROR add image to album: " << query.lastError();
    }
    return getLastInsert();
}

int DataBase::addAlbum(QString name, int position){
   qDebug() << "Add album :" << name << " | pos:" << position;

   QSqlQuery query;
   query.prepare("INSERT INTO albums (name, position) VALUES(?, ?)");
   query.addBindValue(name);
   query.addBindValue(position);
   if(!query.exec()){
       qDebug() << "ERROR add album: " << query.lastError();
   }
   return getLastInsert();
}

void DataBase::deleteImage(int id){
    QSqlQuery query;
    query.prepare("DELETE FROM images where id = ?");
    query.addBindValue(id);
    if(!query.exec()){
        qDebug() << "ERROR delete image: " << query.lastError();
    }
}

void DataBase::deleteAlbum(int id){
    QSqlQuery query;
    query.prepare("DELETE FROM albums WHERE id = ?");
    query.addBindValue(id);
    if(!query.exec()){
        qDebug() << "ERROR delete album: " << query.lastError();
    }
}

QStandardItemModel* DataBase::getAlbums(){
    QSqlQuery query("SELECT * FROM albums");
    QStandardItemModel *albumModel = new QStandardItemModel;

    int idName = query.record().indexOf("name");
    int idId = query.record().indexOf("id");

    while (query.next()) {
        QStandardItem *item = new QStandardItem;
        item->setIcon(QIcon(":/ressources/images/defaultA.png"));
        item->setText(query.value(idName).toString());
        item->setData(query.value(idId).toInt());
        albumModel->appendRow(item);
        qDebug() << " +get album id:" << item->data() << " | " << item->text();
    }

    qDebug() << "Get Album: " << albumModel->rowCount();
    return albumModel;
}

Image* DataBase::getImageByPath(QString path){
    QSqlQuery query;
    query.prepare("SELECT * FROM images WHERE path = ?");
    query.addBindValue(path);

    bool ok = query.exec();
    if(!ok){
        qDebug() << "ERROR GetImageByPath " << query.lastError();
        return new Image();
    }

    int idId = query.record().indexOf("id");
    int idPath = query.record().indexOf("path");
    int idDescription = query.record().indexOf("description");
    int idTags = query.record().indexOf("tags");
    int idScore = query.record().indexOf("score");

    query.first();
    return new Image(
                query.value(idId).toInt(),
                query.value(idPath).toString(),
                query.value(idDescription).toString(),
                query.value(idTags).toString(),
                query.value(idScore).toInt()
                );
}

Image* DataBase::getImageById(int id){
    QSqlQuery query;
    query.prepare("SELECT * FROM images WHERE id = ?");
    query.addBindValue(id);

    bool ok = query.exec();
    if(!ok){
        qDebug() << "ERROR GetImageById " << query.lastError();
        return new Image();
    }

    int idId = query.record().indexOf("id");
    int idPath = query.record().indexOf("path");
    int idDescription = query.record().indexOf("description");
    int idTags = query.record().indexOf("tags");
    int idScore = query.record().indexOf("score");

    query.first();
    return new Image(
                query.value(idId).toInt(),
                query.value(idPath).toString(),
                query.value(idDescription).toString(),
                query.value(idTags).toString(),
                query.value(idScore).toInt()
                );
}

QStandardItemModel* DataBase::getImagesFromAlbum(int albumId){
    QSqlQuery query;
    QStandardItemModel *albumImgModel = new QStandardItemModel;

    query.prepare("SELECT * FROM albumImages WHERE idAlbum = ?");
    query.addBindValue(albumId);
    query.exec();

    int idIdImage = query.record().indexOf("idImage");

    while (query.next()) {        
        int idImage = query.value(idIdImage).toInt();

        Image *image = getImageById(idImage);
        QStringList parts = image->path.split("/");
        QString filename = parts.at(parts.size()-1);

        QStandardItem *item = new QStandardItem;
        item->setText(filename);
        item->setData(QVariant::fromValue(*image));

        albumImgModel->appendRow(item);
        qDebug() << " +get image " << item->text() << " | " << item->data();
    }

    qDebug() << "Get Image: " << albumImgModel->rowCount() << " | idA:" << albumId;
    return albumImgModel;
}



// TO UPDATE
void DataBase::updateAlbum(int id, QString name, int position){
    qDebug() << "UPDATE ALBUM id:" << id << " | n:" << name << " | pos:" << position;
    QSqlQuery query;
    query.prepare("UPDATE albums SET name = ?, position = ? WHERE id = ?");
    query.addBindValue(name);
    query.addBindValue(position);
    query.addBindValue(id);

    if(!query.exec()){
        qDebug() << "ERROR update album: " << query.lastError();
    }
}

void DataBase::updateImage(int id, int position, int idAlbum){
    QSqlQuery query;
    query.prepare("UPDATE images set position = ?, idAlbum = ? WHERE id = ?");
    query.addBindValue(position);
    query.addBindValue(idAlbum);
    query.addBindValue(id);

    if(!query.exec()){
        qDebug() << "ERROR update image: " << query.lastError();
    }
}
