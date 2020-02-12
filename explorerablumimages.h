#ifndef EXPLORERABLUMIMAGES_H
#define EXPLORERABLUMIMAGES_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QDockWidget>
#include "database.h"
#include "widgets/explorerimg.h"
#include "models/imageswitcher.h"

namespace Ui {
class ExplorerAblumImages;
}

class ExplorerAblumImages : public QMainWindow
{
    Q_OBJECT

public:
    explicit ExplorerAblumImages(QWidget *parent = nullptr);
    ~ExplorerAblumImages();
    QDockWidget *imgDock;
    ExplorerImg *explImg;
    QFuture<void> thumbsLoader;
    void loadImages(int albumID);

signals:
    void returnFromAlbum();
    void openImage(ImageSwitcher*);

private slots:
    void returnFrom();
    void openImagesDrawer();
    void imageDrawerChange(bool visible);
    void onImageClick(QModelIndex item);
    void onAlbumImageModelChange(QStandardItem *item);
    void openImageFromDrawer(ImageSwitcher*);
    void editTitle();
    void removeImage();
    void reorderImage();
    void slideShow();

private:
    Ui::ExplorerAblumImages *ui;
    QStandardItemModel *albumImageModel;
    DataBase *db;
    int albumID;
    void loadThumbs(QStandardItemModel *model);
    QString albumTitle;
    bool reorderMode;
};

#endif // EXPLORERABLUMIMAGES_H
