#ifndef EXPLORERABLUMIMAGES_H
#define EXPLORERABLUMIMAGES_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QDockWidget>
#include "database.h"
#include "widgets/explorerimg.h"

namespace Ui {
class ExplorerAblumImages;
}

class ExplorerAblumImages : public QMainWindow
{
    Q_OBJECT

public:
    explicit ExplorerAblumImages(QWidget *parent = nullptr);
    ~ExplorerAblumImages();
    bool isImgVisible;
    QDockWidget *imgDock;
    ExplorerImg *explImg;
    QFuture<void> thumbsLoader;
    void loadImages(int albumID);

signals:
    void returnFromAlbum();
    void openImage(Image image);

private slots:
    void returnFrom();
    void openImagesDrawer();
    void onImageClick(QModelIndex item);

private:
    Ui::ExplorerAblumImages *ui;
    QStandardItemModel *albumImageModel;
    DataBase *db;
    void loadThumbs(QStandardItemModel *model);
};

#endif // EXPLORERABLUMIMAGES_H
