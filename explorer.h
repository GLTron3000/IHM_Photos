#ifndef EXPLORER_H
#define EXPLORER_H

#include <QMainWindow>
#include <QToolBar>
#include "explorerablumimages.h"
#include "exploreralbums.h"
#include "imageswitcher.h"

namespace Ui {
class Explorer;
}

class Explorer : public QMainWindow
{
    Q_OBJECT

public:
    explicit Explorer(QWidget *parent = nullptr);
    ~Explorer();

signals:
    void openImageFromAlbum(Image);

private slots:
    void showAlbums();
    void showAlbumImages(int albumID);
    void openImage(ImageSwitcher *switcher);

private:
    Ui::Explorer *ui;
    ExplorerAlbums *albums;
    ExplorerAblumImages *images;
    QToolBar *toolbar;
};

#endif // EXPLORER_H
