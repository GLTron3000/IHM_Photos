#include "database.h"


DataBase::DataBase()
{
    const QString DRIVER("QSQLITE");
    if(!QSqlDatabase::isDriverAvailable(DRIVER)) qDebug() << "Driver not Available";

    m_db = QSqlDatabase::addDatabase(DRIVER);
    m_db.setDatabaseName("TestPreferences");
    bool ok = m_db.open();
    if(!ok) qWarning() << "ERROR: " << m_db.lastError();

    m_db.exec("CREATE TABLE IF NOT EXISTS album (id INTERGER PRIMARY KEY, name TEXT UNIQUE, index INTEGER UNIQUE)");
    m_db.exec("CREATE TABLE IF NOT EXISTS photo (id INTERGER PRIMARY KEY, path TEXT, index INTEGER, albumId INTEGER)");

    m_db.exec("CREATE TABLE IF NOT EXISTS source (id INTERGER PRIMARY KEY, path TEXT)");
}


//ajouter/supprimer photo/album
void DataBase::addImg(QString path, int idAlbum){
    QSqlQuery query;
    query.prepare("INSERT INTO photo(path,index) VALUES(?,?)");
    query.addBindValue(path);
    query.addBindValue(idAlbum);
    query.exec();
}

void DataBase::deleteImg(int id){
    QSqlQuery query;
    query.prepare("DELETE FROM image where id = ?");
    query.addBindValue(id);
    query.exec();
}

void DataBase::addAlbum(QString name, int index){
   QSqlQuery query;
   query.prepare("INSERT INTO album(name,index) VALUES(?,?)");
   query.addBindValue(name);
   query.addBindValue(index);
   query.exec();
}

void DataBase::deleteAlbum(int id){
    QSqlQuery query;
    query.prepare("DELETE FROM album WHERE id = ?");
    query.addBindValue(id);
    query.exec();
}

QStandardItemModel* DataBase::getAlbum(){
    QSqlQuery query;
    query.prepare("SELECT * FROM album");
    QStandardItemModel *albumModel = new QStandardItemModel;
    while (query.next()) {
        QStandardItem *item = new QStandardItem;
        item->setText(query.value(0).toString());
        item->setData(query.value(1).toString());
        albumModel->appendRow(item);
    }
    return albumModel;
}

QStandardItemModel* DataBase::getImage(int albumId){
    QSqlQuery query;
    query.prepare("SELECT * FROM image WHERE albumId = ?");
    query.addBindValue(albumId);
    QStandardItemModel *albumImgModel = new QStandardItemModel;
    while (query.next()) {
        QStandardItem *item = new QStandardItem;
        item->setText(query.value(0).toString());
        item->setData(query.value(1).toString());
        albumImgModel->appendRow(item);
    }
    return albumImgModel;
}

void DataBase::updateAlbum(int id, QString name, int index){
    QSqlQuery query;
    query.prepare("UPDATE album set name = ?, index = = ? WHERE id = ?");
    query.addBindValue(name);
    query.addBindValue(index);
    query.addBindValue(id);
    query.exec();
}

void DataBase::updateImage(int id, int index, int idAlbum){
    QSqlQuery query;
    query.prepare("UPDATE image set index = ?, idAlbum = = ? WHERE id = ?");
    query.addBindValue(index);
    query.addBindValue(idAlbum);
    query.addBindValue(id);
    query.exec();
}
