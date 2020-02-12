#ifndef EXPLORER_H
#define EXPLORER_H

#include <QMainWindow>
#include <QToolBar>
#include "explorerablumimages.h"
#include "exploreralbums.h"
#include "models/imageswitcher.h"

namespace Ui {
class Explorer;
}

class Explorer : public QMainWindow
{
    Q_OBJECT

public:
    explicit Explorer(QWidget *parent = nullptr);
    ~Explorer();

public slots:
    void reload();
    void newAlbum();
    void slideshow();
    void changeOrder();
    void back();
    void imageDrawer();
    void editTitle();

signals:
    void openImageFromAlbum(ImageSwitcher *);
    void switchMenuBar(bool);

private slots:
    void showAlbums();
    void showAlbumImages(int albumID);
    void openImage(ImageSwitcher *switcher);

private:
    Ui::Explorer *ui;
    ExplorerAlbums *albums;
    ExplorerAblumImages *images;
    QToolBar *toolbar;
    int currentAlbum;
    bool albumMode;
};

#endif // EXPLORER_H
