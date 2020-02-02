#ifndef VISIONNEUSE_H
#define VISIONNEUSE_H

#include <QWidget>
#include <QLabel>
#include <QMainWindow>
#include "customObjects/graphicsviewzoom.h"
#include "customObjects/clipscene.h"

namespace Ui {
class Visionneuse;
}

class Visionneuse : public QMainWindow
{
    Q_OBJECT

public:
    explicit Visionneuse(QWidget *parent = nullptr);
    ~Visionneuse();
    void afficherImage(QString path);
    QString imagePath;

private:
    Ui::Visionneuse *ui; 

    ClipScene* clipScene;
    GraphicsViewZoom *graphicsViewZoom;


public slots:
    void zoomIn();
    void zoomOut();
    void restaurerTailleImg();
};

#endif // VISIONNEUSE_H
