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

enum EditMode{
   none,
   crop,
   resize
};

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
    EditMode editMode = none;


public slots:
    void zoomIn();
    void zoomOut();
    void restaurerTailleImg();
    void crop();
    void resize();
};

#endif // VISIONNEUSE_H
