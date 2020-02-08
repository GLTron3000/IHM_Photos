#ifndef EXPLORERIMG_H
#define EXPLORERIMG_H

#include <QWidget>
#include <QStandardItemModel>
#include "database.h"
#include "models/imageswitcher.h"

namespace Ui {
class ExplorerImg;
}

class ExplorerImg : public QWidget
{
    Q_OBJECT

public:
    explicit ExplorerImg(QWidget *parent = nullptr);
    ~ExplorerImg();

public slots:
    void loadImages();

signals:
    void openImage(ImageSwitcher*);

private:
    Ui::ExplorerImg *ui;
    QStandardItemModel *imagesModel;
    QStandardItemModel *imagesSearchModel;
    DataBase *db;
    QFuture<void> thumbsLoader;

private slots:
    void searchList(QString);
     void onImageClick(QModelIndex item);

private:
    void loadPath(QString path);
    void loadThumbs(QStandardItemModel *model);
    bool isSupportedFormat(QString format);
};

#endif // EXPLORERIMG_H
