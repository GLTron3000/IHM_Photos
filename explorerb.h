#ifndef EXPLORERB_H
#define EXPLORERB_H

#include <QMainWindow>
#include <QToolBar>
#include "explorerablumimages.h"
#include "exploreralbums.h"

namespace Ui {
class ExplorerB;
}

class ExplorerB : public QMainWindow
{
    Q_OBJECT

public:
    explicit ExplorerB(QWidget *parent = nullptr);
    ~ExplorerB();

signals:
    void openImageFromAlbum(Image);

private slots:
    void showAlbums();
    void showAlbumImages(int albumID);
    void openImage(Image image);

private:
    Ui::ExplorerB *ui;
    ExplorerAlbums *albums;
    ExplorerAblumImages *images;
    QToolBar *toolbar;
};

#endif // EXPLORERB_H
