#include "database.h"


DataBase::DataBase()
{
    const QString DRIVER("QSQLITE");
    if(!QSqlDatabase::isDriverAvailable(DRIVER)) qDebug() << "Driver not Available";

    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("/home/thomsb/Projets/qt/IHM_Photos/testo2.sqlite");
    if(!m_db.open()) qDebug() << "ERROR: " << m_db.lastError();
    else qDebug() << "Database ok";

    QSqlQuery query;
    bool ok = query.exec("CREATE TABLE IF NOT EXISTS album (id INTERGER PRIMARY KEY, name TEXT UNIQUE, position INTEGER UNIQUE)");
    if(!ok) qDebug() << "ERROR create album ";
    ok = query.exec("CREATE TABLE IF NOT EXISTS photo (id INTERGER PRIMARY KEY, path TEXT, position INTEGER, albumId INTEGER)");
    if(!ok) qDebug() << "ERROR create photo ";
    ok = query.exec("CREATE TABLE IF NOT EXISTS source (id INTERGER PRIMARY KEY, path TEXT)");
    if(!ok) qDebug() << "ERROR create source ";

}


//ajouter/supprimer photo/album
void DataBase::addImg(QString path, int idAlbum){
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO photo(path,position) VALUES(?,?)");
    query.addBindValue(path);
    query.addBindValue(idAlbum);
    if(!query.exec()){
        qDebug() << "ERROR add image: " << query.lastError();
    }
}

void DataBase::deleteImg(int id){
    QSqlQuery query(m_db);
    query.prepare("DELETE FROM image where id = ?");
    query.addBindValue(id);
    if(!query.exec()){
        qDebug() << "ERROR delete image: " << query.lastError();
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

void DataBase::deleteAlbum(int id){
    QSqlQuery query;
    query.prepare("DELETE FROM album WHERE id = ?");
    query.addBindValue(id);
    if(!query.exec()){
        qDebug() << "ERROR delete album: " << query.lastError();
    }
}

QStandardItemModel* DataBase::getAlbum(){
    QSqlQuery query("SELECT * FROM album");
    QStandardItemModel *albumModel = new QStandardItemModel;

    int idName = query.record().indexOf("name");
    int idPosition = query.record().indexOf("position");

    while (query.next()) {
        QStandardItem *item = new QStandardItem;
        item->setIcon(QIcon(":/ressources/images/defaultA.png"));
        item->setText(query.value(idName).toString());
        item->setData(query.value(idPosition).toString());
        albumModel->appendRow(item);
        qDebug() << " +get album";
    }

    qDebug() << "Get Album: " << albumModel->rowCount();
    return albumModel;
}

QStandardItemModel* DataBase::getImage(int albumId){
    QSqlQuery query;

    query.prepare("SELECT * FROM image WHERE albumId = ?");
    query.addBindValue(albumId);

    QStandardItemModel *albumImgModel = new QStandardItemModel;

    while (query.next()) {
        QStandardItem *item = new QStandardItem;
        item->setText(query.value(1).toString());
        item->setData(query.value(0).toString());
        albumImgModel->appendRow(item);
    }

    return albumImgModel;
}

void DataBase::updateAlbum(int id, QString name, int index){
    QSqlQuery query;
    query.prepare("UPDATE album set name = ?, position = = ? WHERE id = ?");
    query.addBindValue(name);
    query.addBindValue(index);
    query.addBindValue(id);
    query.exec();
}

void DataBase::updateImage(int id, int index, int idAlbum){
    QSqlQuery query;
    query.prepare("UPDATE image set position = ?, idAlbum = = ? WHERE id = ?");
    query.addBindValue(index);
    query.addBindValue(idAlbum);
    query.addBindValue(id);
    query.exec();
}
