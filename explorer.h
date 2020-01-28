#ifndef EXPLORER_H
#define EXPLORER_H

#include <QWidget>
#include <QFuture>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class Explorer; }
QT_END_NAMESPACE

class Explorer : public QWidget
{
    Q_OBJECT

public:
    QStandardItemModel *imagesModel;
    QStandardItemModel *albumModel;

public:
    explicit Explorer(QWidget *parent = nullptr);
    ~Explorer();
    void loadImages();
    void loadAlbums();

signals:
    void openImage(QString path);

private slots:
    void onImageClick(QModelIndex);
    void onAlbumClick(QModelIndex);
    void onRefreshClick();
    void onAlbumAddClick();
    void onAlbumModelChange(QStandardItem*);

private:
    Ui::Explorer *ui;

private:
    void loadPath(QString path);
    void loadThumbs();
};

#endif // EXPLORER_H
