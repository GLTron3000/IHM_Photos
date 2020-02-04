#ifndef RESIZEIMGWIDGET_H
#define RESIZEIMGWIDGET_H

#include <QWidget>

namespace Ui {
class ResizeImgWidget;
}

class ResizeImgWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ResizeImgWidget(QWidget *parent = nullptr);
    ~ResizeImgWidget();

private:
    Ui::ResizeImgWidget *ui;
};

#endif // RESIZEIMGWIDGET_H
