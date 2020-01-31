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
    bool ok = query.exec("CREATE TABLE IF NOT EXISTS albums (id INTERGER PRIMARY KEY, name TEXT UNIQUE NOT NULL, position INTEGER UNIQUE NOT NULL)");
    if(!ok) qDebug() << "ERROR create albums ";
    ok = query.exec("CREATE TABLE IF NOT EXISTS images (id INTERGER PRIMARY KEY, path TEXT NOT NULL, score INTEGER NOT NULL, description TEXT, keyword TEXT)");
    if(!ok) qDebug() << "ERROR create images ";
    ok = query.exec("CREATE TABLE IF NOT EXISTS albumImages (id INTERGER PRIMARY KEY, idImage INTEGER NOT NULL, idAlbum INTEGER NOT NULL, position INTEGER NOT NULL)");
    if(!ok) qDebug() << "ERROR create albumImages ";

    ok = query.exec("CREATE TABLE IF NOT EXISTS source (id INTERGER PRIMARY KEY, path TEXT NOT NULL)");
    if(!ok) qDebug() << "ERROR create source ";

}


//ajouter/supprimer photo/album
void DataBase::addImage(QString path, int position, int idAlbum){
    qDebug() << "Add image :" << path << " | i:" << position << " | idA:" << idAlbum;
    QSqlQuery query;

    query.prepare("INSERT INTO images (path, score, description, keyword) VALUES(?,?,?,?)");
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
}

void DataBase::addAlbum(QString name, int position){
   qDebug() << "Add album :" << name << " | i:" << position;
   QSqlQuery query;
   query.prepare("INSERT INTO album(name, position) VALUES(?, ?)");
   query.addBindValue(name);
   query.addBindValue(position);
   if(!query.exec()){
       qDebug() << "ERROR add album: " << query.lastError();
   }
}

void DataBase::deleteImage(int id){
    QSqlQuery query;
    query.prepare("DELETE FROM image where id = ?");
    query.addBindValue(id);
    if(!query.exec()){
        qDebug() << "ERROR delete image: " << query.lastError();
    }
}

void DataBase::deleteAlbum(int id){
    QSqlQuery query;
    query.prepare("DELETE FROM album WHERE id = ?");
    query.addBindValue(id);
    if(!query.exec()){
        qDebug() << "ERROR delete album: " << query.lastError();
    }
}

QStandardItemModel* DataBase::getAlbums(){
    QSqlQuery query("SELECT * FROM album");
    QStandardItemModel *albumModel = new QStandardItemModel;

    int idName = query.record().indexOf("name");
    int idPosition = query.record().indexOf("position");

    while (query.next()) {
        QStandardItem *item = new QStandardItem;
        item->setIcon(QIcon(":/ressources/images/defaultA.png"));
        item->setText(query.value(idName).toString());
        item->setData(query.value(idPosition).toInt());
        albumModel->appendRow(item);
        qDebug() << " +get album id:" << item->data() << " | " << item->text();
    }

    qDebug() << "Get Album: " << albumModel->rowCount();
    return albumModel;
}

Image* DataBase::getImageByPath(QString path){
    qDebug() << "GET IMAGE BY PATH: " << path;
    QSqlQuery query;
    query.prepare("SELECT * FROM images WHERE path = ?");
    query.addBindValue(path);
    query.exec();

    int idId = query.record().indexOf("id");
    int idPath = query.record().indexOf("path");
    int idDescription = query.record().indexOf("description");
    int idTags = query.record().indexOf("keyword");
    int idScore = query.record().indexOf("score");

    query.first();
    return new Image(
                query.value(idId).toInt(),
                query.value(idPath).toString(),
                query.value(idDescription).toString(),
                query.value(idTags).toString(),
                query.value(idScore).toInt()
                );

    return new Image();
}

Image* DataBase::getImageById(int id){
    QSqlQuery query;
    query.prepare("SELECT * FROM images WHERE id = ?");
    query.addBindValue(id);
    query.exec();

    int idId = query.record().indexOf("id");
    int idPath = query.record().indexOf("path");
    int idDescription = query.record().indexOf("description");
    int idTags = query.record().indexOf("keyword");
    int idScore = query.record().indexOf("score");

    query.first();
    return new Image(
                query.value(idId).toInt(),
                query.value(idPath).toString(),
                query.value(idDescription).toString(),
                query.value(idTags).toString(),
                query.value(idScore).toInt()
                );

    return new Image();
}

QStandardItemModel* DataBase::getImagesFromAlbum(int albumId){
    QSqlQuery query;
    QStandardItemModel *albumImgModel = new QStandardItemModel;

    query.prepare("SELECT * FROM albumImages WHERE idAlbum = ?");
    query.addBindValue(albumId);
    query.exec();

    //int idId = query.record().indexOf("id");
    //int idIdAlbum = query.record().indexOf("idAlbum");
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

void DataBase::updateAlbum(int id, QString name, int position){
    qDebug() << "UPDATE ALBUM id:" << id << " | n:" << name << " | pos:" << position;
    QSqlQuery query;
    query.prepare("UPDATE album SET name = ?, position = ? WHERE id = ?");
    query.addBindValue(name);
    query.addBindValue(position);
    query.addBindValue(id);

    if(!query.exec()){
        qDebug() << "ERROR update album: " << query.lastError();
    }
}

void DataBase::updateImage(int id, int position, int idAlbum){
    QSqlQuery query;
    query.prepare("UPDATE image set position = ?, idAlbum = ? WHERE id = ?");
    query.addBindValue(position);
    query.addBindValue(idAlbum);
    query.addBindValue(id);

    if(!query.exec()){
        qDebug() << "ERROR update image: " << query.lastError();
    }
}
