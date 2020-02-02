#ifndef EXPLORER_H
#define EXPLORER_H

#include <QWidget>
#include <QFuture>
#include <QStandardItemModel>
#include "database.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Explorer; }
QT_END_NAMESPACE

class Explorer : public QWidget
{
    Q_OBJECT

public:
    QStandardItemModel *imagesModel;
    QStandardItemModel *albumModel;
    QStandardItemModel *albumImageModel;
    DataBase *db;

public:
    explicit Explorer(QWidget *parent = nullptr);
    ~Explorer();

signals:
    void openImage(QString path);

public slots:
    void addAlbum();
    void loadAlbums();
    void loadImages();
    void editTitle();
    void returnAlbum();

private slots:
    void onImageClick(QModelIndex);
    void onAlbumClick(QModelIndex);
    void onAlbumModelChange(QStandardItem*);
    void onAlbumImageModelChange(QStandardItem*);
    void onAlbumMoved(QModelIndexList);

private:
    Ui::Explorer *ui;
    int currentAlbum;
    bool editMode;
    bool moveMode;

private:
    void loadPath(QString path);
    void loadThumbs(QStandardItemModel *model);
};

#endif // EXPLORER_H
