#ifndef EXPLORERIMG_H
#define EXPLORERIMG_H

#include <QWidget>
#include <QStandardItemModel>
#include "database.h"

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

private:
    Ui::ExplorerImg *ui;
    QStandardItemModel *imagesModel;
    DataBase *db;
    QFuture<void> thumbsLoader;

private:
    void loadPath(QString path);
    void loadThumbs(QStandardItemModel *model);
};

#endif // EXPLORERIMG_H
