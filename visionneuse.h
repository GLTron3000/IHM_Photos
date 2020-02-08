#ifndef VISIONNEUSE_H
#define VISIONNEUSE_H

#include <QWidget>
#include <QLabel>
#include <QMainWindow>
#include <QtWidgets>
#include <QToolBar>

#include "widgets/info.h"
#include "widgets/graphicsviewzoom.h"
#include "models/imageswitcher.h"


namespace Ui {
class Visionneuse;
}

class Visionneuse : public QMainWindow
{
    Q_OBJECT

public:
    explicit Visionneuse(QWidget *parent = nullptr, ImageSwitcher *imageSwitcher = nullptr);
    ~Visionneuse();
    void afficherImage(QString path);
    QString imagePath;
    QGraphicsPixmapItem *imagePixmap;

signals:
    void closeVisio();

private:
    Ui::Visionneuse *ui; 

    Info* info;
    QGraphicsScene *scene;
    GraphicsViewZoom *graphicsViewZoom;

    QListWidget *labelList;
    QListWidget *buttonList;

    ImageSwitcher *imageSwitcher;

    QToolBar *toolbar;
    QMenu *viewMenu; ///////////

    QDockWidget *dock;
    bool visibleInfo=false;

    void createDockWindows();


public slots:
    void zoomIn();
    void zoomOut();
    void restaurerTailleImg();
    void crop();
    void resize();
    void afficherInformations();
    void rotationPlus();
    void rotationMinus();
    void save();
    void saveAs();
    void close();
    void imagePrecedente();
    void imageSuivante();
};

#endif // VISIONNEUSE_H
