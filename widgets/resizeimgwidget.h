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
    explicit ResizeImgWidget(QWidget *parent = nullptr,  int height = -1, int width = -1);
    ~ResizeImgWidget();
    int height;
    int width;

signals:
    void changeResolution(int, int);

private slots:
    void accept();
    void abort();
    void checkRatio();
    void heightChange(int);
    void widthChange(int);


private:
    Ui::ResizeImgWidget *ui;
    double ratioH;
    double ratioW;
    bool useRatio;
    bool signalBlock;
};

#endif // RESIZEIMGWIDGET_H
