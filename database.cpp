#include "database.h"


DataBase::DataBase()
{
    /*const QString DRIVER("QSQLITE");
    if(!QSqlDatabase::isDriverAvailable(DRIVER)) qDebug() << "Driver not Available";
    */
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(":testo:");
    bool ok = m_db.open();
    if(!ok) qWarning() << "ERROR: " << m_db.lastError();

    QSqlQuery query;
    ok = query.exec("CREATE TABLE IF NOT EXISTS album (id INTERGER PRIMARY KEY, name TEXT UNIQUE, position INTEGER UNIQUE)");
    if(!ok) qWarning() << "ERROR create album ";
    ok = query.exec("CREATE TABLE IF NOT EXISTS photo (id INTERGER PRIMARY KEY, path TEXT, position INTEGER, albumId INTEGER)");
    if(!ok) qWarning() << "ERROR create photo ";
    ok = query.exec("CREATE TABLE IF NOT EXISTS source (id INTERGER PRIMARY KEY, path TEXT)");
    if(!ok) qWarning() << "ERROR create source ";

}


//ajouter/supprimer photo/album
void DataBase::addImg(QString path, int idAlbum){
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO photo(path,position) VALUES(?,?)");
    query.addBindValue(path);
    query.addBindValue(idAlbum);
    bool ok = query.exec();
    if(!ok) qWarning() << "ERROR add img ";
}

void DataBase::deleteImg(int id){
    QSqlQuery query(m_db);
    query.prepare("DELETE FROM image where id = ?");
    query.addBindValue(id);
    query.exec();
}

void DataBase::addAlbum(QString name, int index){
   QSqlQuery query;
   query.prepare("INSERT INTO album(name,position) VALUES(?,?)");
   query.addBindValue(name);
   query.addBindValue(index);
   bool ok = query.exec();
   if(!ok) qWarning() << "ERROR add album ";
}

void DataBase::deleteAlbum(int id){
    QSqlQuery query(m_db);
    query.prepare("DELETE FROM album WHERE id = ?");
    query.addBindValue(id);
    query.exec();
}

QStandardItemModel* DataBase::getAlbum(){
    QSqlQuery query(m_db);
    query.prepare("SELECT * FROM album");
    QStandardItemModel *albumModel = new QStandardItemModel;
    while (query.next()) {
        QStandardItem *item = new QStandardItem;
        item->setText(query.value(1).toString());
        item->setData(query.value(0).toString());
        albumModel->appendRow(item);
    }
    return albumModel;
}

QStandardItemModel* DataBase::getImage(int albumId){
    QSqlQuery query(m_db);
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
    QSqlQuery query(m_db);
    query.prepare("UPDATE album set name = ?, position = = ? WHERE id = ?");
    query.addBindValue(name);
    query.addBindValue(index);
    query.addBindValue(id);
    query.exec();
}

void DataBase::updateImage(int id, int index, int idAlbum){
    QSqlQuery query(m_db);
    query.prepare("UPDATE image set position = ?, idAlbum = = ? WHERE id = ?");
    query.addBindValue(index);
    query.addBindValue(idAlbum);
    query.addBindValue(id);
    query.exec();
}
