#ifndef EXPLORERALBUMS_H
#define EXPLORERALBUMS_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <database.h>

namespace Ui {
class ExplorerAlbums;
}

class ExplorerAlbums : public QMainWindow
{
    Q_OBJECT

public:
    explicit ExplorerAlbums(QWidget *parent = nullptr);
    ~ExplorerAlbums();

signals:
    void openAlbum(int albumID);

public slots:
    void addAlbum();
    void loadAlbums();
    void editTitle();

private slots:
    void onAlbumClick(QModelIndex);
    void onAlbumMoved(QModelIndexList);
    void searchList(QString name);

private:
    Ui::ExplorerAlbums *ui;
    QStandardItemModel *albumModel;
    QStandardItemModel *albumSearchModel;
    DataBase *db;
    bool editMode;
};

#endif // EXPLORERALBUMS_H
