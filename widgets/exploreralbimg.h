#ifndef EXPLORERALBIMG_H
#define EXPLORERALBIMG_H

#include <QWidget>
#include <QDockWidget>
#include "explorerimg.h"

namespace Ui {
class ExplorerAlbImg;
}

class ExplorerAlbImg : public QWidget
{
    Q_OBJECT

public:
    explicit ExplorerAlbImg(QWidget *parent = nullptr);
    ~ExplorerAlbImg();
    void afficherImg();
    bool isImgVisible;
    QDockWidget *imgDock;
    ExplorerImg *explImg;

private:
    Ui::ExplorerAlbImg *ui;
};

#endif // EXPLORERALBIMG_H
