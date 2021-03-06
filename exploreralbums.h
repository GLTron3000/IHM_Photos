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

private slots:
    void onAlbumClick(QModelIndex);
    void searchList(QString name);
    void deleteAlbum();

private:
    Ui::ExplorerAlbums *ui;
    QStandardItemModel *albumModel;
    QStandardItemModel *albumSearchModel;
    QSortFilterProxyModel *proxyModel;
    DataBase *db;
    bool editMode;
    bool searchMode;
};

#endif // EXPLORERALBUMS_H
