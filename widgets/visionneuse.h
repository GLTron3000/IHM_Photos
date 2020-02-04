#ifndef VISIONNEUSE_H
#define VISIONNEUSE_H

#include "widgets/info.h"

#include <QWidget>
#include <QLabel>
#include <QMainWindow>
#include "customObjects/graphicsviewzoom.h"
#include "customObjects/clipscene.h"
#include "QListWidget"
#include <QtWidgets>
/*#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printdialog)
#include <QtPrintSupport>
#endif
#endif*/

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
    QGraphicsPixmapItem *imagePixmap;

private:
    Ui::Visionneuse *ui; 

    Info* info;
    QGraphicsScene *scene;
    ClipScene* clipScene;
    GraphicsViewZoom *graphicsViewZoom;
    EditMode editMode = none;

    QListWidget *labelList;
    QListWidget *buttonList;
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
    void informations();
    void save();
    void saveAs();
};

#endif // VISIONNEUSE_H
