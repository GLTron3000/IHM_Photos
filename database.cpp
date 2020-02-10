#include "database.h"

DataBase::DataBase()
{
    const QString DRIVER("QSQLITE");
    if(!QSqlDatabase::isDriverAvailable(DRIVER)) qDebug() << "Driver not Available";

    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("ultraphoto2000DB.sqlite");
    if(!m_db.open()) qDebug() << "ERROR: " << m_db.lastError();
    else qDebug() << "Database ok";

    QSqlQuery query;
    if(!query.exec("CREATE TABLE IF NOT EXISTS albums (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT UNIQUE NOT NULL)"))
        qDebug() << "ERROR create albums " << query.lastError();
    if(!query.exec("CREATE TABLE IF NOT EXISTS images (id INTEGER PRIMARY KEY AUTOINCREMENT, path TEXT UNIQUE NOT NULL, score INTEGER NOT NULL, description TEXT, tags TEXT, feel TEXT)"))
        qDebug() << "ERROR create images " << query.lastError();
    if(!query.exec("CREATE TABLE IF NOT EXISTS albumImages (id INTEGER PRIMARY KEY AUTOINCREMENT, idImage INTEGER NOT NULL, idAlbum INTEGER NOT NULL, position INTEGER NOT NULL)"))
        qDebug() << "ERROR create albumImages " << query.lastError();

    if(!query.exec("CREATE TABLE IF NOT EXISTS sources (id INTEGER PRIMARY KEY AUTOINCREMENT, path TEXT NOT NULL)"))
        qDebug() << "ERROR create sources " << query.lastError();
}

int DataBase::getLastInsert(){
    QSqlQuery query("SELECT last_insert_rowid()");
    query.exec();

    return query.lastInsertId().toInt();
}

int DataBase::addImage(QString path){
    qDebug() << "Add image :" << path;
    QSqlQuery query;

    query.prepare("INSERT INTO images (path, score, description, tags, feel) VALUES(?,?,?,?,?)");
    query.addBindValue(path);
    query.addBindValue(0);
    query.addBindValue("");
    query.addBindValue("");
    query.addBindValue("");
    if(!query.exec()){
        qDebug() << "ERROR add image: " << query.lastError();
    }
    return getLastInsert();
}

int DataBase::addImageToAlbum(Image image, int position, int idAlbum){
    qDebug() << "Add imageToAlbum:" << image.path << " | i:" << position << " | idA:" << idAlbum;
    QSqlQuery query;
    QStandardItemModel *albumImages = getImagesFromAlbum(idAlbum);
    //Image *image = getImageByPath(path);
    int albumPosition = albumImages->rowCount();

    query.prepare("INSERT INTO albumImages (idImage, idAlbum, position) VALUES(?,?,?)");
    query.addBindValue(image.id);
    query.addBindValue(idAlbum);
    query.addBindValue(albumPosition);
    if(!query.exec()){
        qDebug() << "ERROR add image to album: " << query.lastError();
    }
    return getLastInsert();
}

int DataBase::addAlbum(QString name){
   qDebug() << "Add album :" << name;

   QSqlQuery query;
   query.prepare("INSERT INTO albums (name) VALUES(?)");
   query.addBindValue(name);
   if(!query.exec()){
       qDebug() << "ERROR add album: " << query.lastError();
   }
   return getLastInsert();
}

void DataBase::addSource(QString path){
    qDebug() << "Add source :" << path;

    QSqlQuery query;
    query.prepare("INSERT INTO sources (path) VALUES(?)");
    query.addBindValue(path);
    if(!query.exec()){
        qDebug() << "ERROR add source: " << query.lastError();
    }
}

void DataBase::deleteImage(int id){
    QSqlQuery query;
    query.prepare("DELETE FROM images where id = ?");
    query.addBindValue(id);
    if(!query.exec()){
        qDebug() << "ERROR delete image: " << query.lastError();
    }
}

void DataBase::deleteImageFromAlbum(int albumId, int imageId){
    QSqlQuery query;
    query.prepare("DELETE FROM albumImages where idImage = ? AND idAlbum = ?");
    query.addBindValue(imageId);
    query.addBindValue(albumId);
    if(!query.exec()){
        qDebug() << "ERROR delete imageFromAlbum: " << query.lastError();
    }
}

void DataBase::deleteImageFromAll(int imageId){
    QSqlQuery query;
    query.prepare("DELETE FROM albumImages where idImage = ?");
    query.addBindValue(imageId);
    if(!query.exec()){
        qDebug() << "ERROR delete imageFromAll " << query.lastError();
    }
}

void DataBase::deleteAlbumImages(int albumId){
    QSqlQuery query;
    query.prepare("DELETE FROM albumImages where idAlbum = ?");
    query.addBindValue(albumId);
    if(!query.exec()){
        qDebug() << "ERROR delete albumImages: " << query.lastError();
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

void DataBase::deleteSource(QString path){
    QSqlQuery query;
    query.prepare("DELETE FROM sources WHERE path = ?");
    query.addBindValue(path);
    if(!query.exec()){
        qDebug() << "ERROR delete source: " << query.lastError();
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

QString DataBase::getAlbumName(int id){
    QSqlQuery query;
    query.prepare("SELECT * FROM albums WHERE id = ?");
    query.addBindValue(id);

    bool ok = query.exec();
    if(!ok){
        qDebug() << "ERROR GetAlbumName " << query.lastError();
        return "";
    }

    int idName = query.record().indexOf("name");

    query.first();
    return query.value(idName).toString();
}

QStringList* DataBase::getSources(){
    QSqlQuery query("SELECT * FROM sources");
    QStringList *pathList = new QStringList();

    int idPath = query.record().indexOf("path");

    while (query.next()) {
        pathList->append(query.value(idPath).toString());
    }

    return pathList;
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
    int idFeel = query.record().indexOf("feel");

    if(!query.first()) return new Image(-1, path,  "", "", 0, "");
    return new Image(
                query.value(idId).toInt(),
                query.value(idPath).toString(),
                query.value(idDescription).toString(),
                query.value(idTags).toString(),
                query.value(idScore).toInt(),
                query.value(idFeel).toString()
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
    int idFeel = query.record().indexOf("feel");

    query.first();
    return new Image(
                query.value(idId).toInt(),
                query.value(idPath).toString(),
                query.value(idDescription).toString(),
                query.value(idTags).toString(),
                query.value(idScore).toInt(),
                query.value(idFeel).toString()
                );
}

QStandardItemModel* DataBase::getImagesFromAlbum(int albumId){
    QSqlQuery query;
    QStandardItemModel *albumImgModel = new QStandardItemModel;

    query.prepare("SELECT * FROM albumImages WHERE idAlbum = ?");
    query.addBindValue(albumId);
    query.exec();

    int idIdImage = query.record().indexOf("idImage");
    int idPosition = query.record().indexOf("position");

    while (query.next()) {        
        int idImage = query.value(idIdImage).toInt();

        Image *image = getImageById(idImage);
        QStringList parts = image->path.split("/");
        QString filename = parts.at(parts.size()-1);

        QStandardItem *item = new QStandardItem;
        item->setText(filename);
        item->setData(QVariant::fromValue(*image));
        item->setFlags(item->flags() ^ (Qt::ItemIsDropEnabled));

        albumImgModel->setItem(query.value(idPosition).toInt(), item);
        qDebug() << " +get image " << item->text() << " | " << item->data() << " at pos: "<< item->row();
    }

    qDebug() << "Get Image: " << albumImgModel->rowCount() << " | idA:" << albumId;
    return albumImgModel;
}

void DataBase::updateAlbum(int id, QString name){
    qDebug() << "UPDATE ALBUM id:" << id << " | n:" << name;
    QSqlQuery query;
    query.prepare("UPDATE albums SET name = ? WHERE id = ?");
    query.addBindValue(name);
    query.addBindValue(id);

    if(!query.exec()){
        qDebug() << "ERROR update album: " << query.lastError();
    }
}

void DataBase::updateAlbumImage(int position, int idAlbum, int idImage){
    QSqlQuery query;
    query.prepare("UPDATE albumImages set position = ? WHERE idAlbum = ? AND idImage = ?");
    query.addBindValue(position);
    query.addBindValue(idAlbum);
    query.addBindValue(idImage);

    if(!query.exec()){
        qDebug() << "ERROR update image: " << query.lastError();
    }
}

void DataBase::updateImage(int id, QString path, int score, QString description, QString tags, QString feel){
    QSqlQuery query;
    query.prepare("UPDATE images set path = ?, score = ?, description = ?, tags = ?, feel = ? WHERE id = ?");
    query.addBindValue(path);
    query.addBindValue(score);
    query.addBindValue(description);
    query.addBindValue(tags);
    query.addBindValue(feel);
    query.addBindValue(id);

    if(!query.exec()){
        qDebug() << "ERROR update image: " << query.lastError();
    }
}

void DataBase::cleaner(){
    QSqlQuery query;
    query.prepare("SELECT * FROM images");
    bool ok = query.exec();
    if(!ok){
        qDebug() << "ERROR cleaner " << query.lastError();
    }

    int idId = query.record().indexOf("id");
    int idPath = query.record().indexOf("path");

    while (query.next()) {
        QString path = query.value(idPath).toString();
        int idImage = query.value(idId).toInt();

        if (FILE *file = fopen(path.toUtf8().constData(), "r")) fclose(file);
        else {
            deleteImage(idImage);
            deleteImageFromAll(idImage);
        }
    }
}

void DataBase::clear(){
    QSqlQuery query;
    query.exec("DROP TABLE IF EXISTS albums");
    query.exec("DROP TABLE IF EXISTS images");
    query.exec("DROP TABLE IF EXISTS albumImages");
    query.exec("DROP TABLE IF EXISTS sources");
}








