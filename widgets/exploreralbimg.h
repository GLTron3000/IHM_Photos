#ifndef EXPLORERALBIMG_H
#define EXPLORERALBIMG_H

#include <QWidget>

namespace Ui {
class explorerAlbImg;
}

class explorerAlbImg : public QWidget
{
    Q_OBJECT

public:
    explicit explorerAlbImg(QWidget *parent = nullptr);
    ~explorerAlbImg();

private:
    Ui::explorerAlbImg *ui;
};

#endif // EXPLORERALBIMG_H
