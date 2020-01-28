#ifndef VISIONNEUSE_H
#define VISIONNEUSE_H

#include <QWidget>

namespace Ui {
class Visionneuse;
}

class Visionneuse : public QWidget
{
    Q_OBJECT

public:
    explicit Visionneuse(QWidget *parent = nullptr);
    ~Visionneuse();
    void afficherImage(QString fileName);

private:
    Ui::Visionneuse *ui;
    QImage image;
    QPixmap *pixmap_img;
    QPixmap pixmap_imgV;
};

#endif // VISIONNEUSE_H
