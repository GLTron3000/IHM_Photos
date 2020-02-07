#ifndef VISIONNEUSE_H
#define VISIONNEUSE_H

#include "widgets/info.h"

#include <QWidget>
#include <QLabel>
#include <QMainWindow>
#include "widgets/graphicsviewzoom.h"
#include "QListWidget"
#include <QtWidgets>
#include <QToolBar>

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
};

#endif // VISIONNEUSE_H
