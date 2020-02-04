#ifndef EXPLORERIMG_H
#define EXPLORERIMG_H

#include <QWidget>

namespace Ui {
class ExplorerImg;
}

class ExplorerImg : public QWidget
{
    Q_OBJECT

public:
    explicit ExplorerImg(QWidget *parent = nullptr);
    ~ExplorerImg();

private:
    Ui::ExplorerImg *ui;
};

#endif // EXPLORERIMG_H
