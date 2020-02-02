#ifndef VISIONNEUSE_H
#define VISIONNEUSE_H

#include <QWidget>
#include <QLabel>
#include <QMainWindow>

namespace Ui {
class Visionneuse;
}

class Visionneuse : public QMainWindow
{
    Q_OBJECT

public:
    explicit Visionneuse(QWidget *parent = nullptr);
    ~Visionneuse();
    void afficherImage(QString fileName);
    QString imagePath;

private:
    Ui::Visionneuse *ui; 
    QImage image;
    QPixmap* pixmap_img;
    QPixmap pixmap_imgV;
    void scaleImg(double scaleFact);
    double m_scaleFactor = 1;
    QLabel *label;
    QSize defaultSize;
    void setDefaultSize();

public slots:
    void zoomIn();
    void zoomOut();
    void restaurerTailleImg();
};

#endif // VISIONNEUSE_H
