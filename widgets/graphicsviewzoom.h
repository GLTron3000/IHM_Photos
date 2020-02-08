#ifndef GRAPHICSVIEWZOOM_H
#define GRAPHICSVIEWZOOM_H

#include <QObject>
#include <QGraphicsView>
#include "widgets/resizablerubberband.h"
#include <QRubberBand>

class GraphicsViewZoom : public QGraphicsView
{
    Q_OBJECT

public:
    explicit GraphicsViewZoom(QWidget *parent = 0);
    void initCrop(ResizableRubberBand *rubber);
    QRubberBand *rubber;
    ResizableRubberBand *rubberR;

private:
    QPoint rubberOrigin;
    QPoint rubberEnd;
    bool rubberDrag;
    bool cropActive;
    bool initialDrag;

public slots:
    void wheelEvent(QWheelEvent* event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void cropMode();
    void scaleAll(double factor);

};

#endif // GRAPHICSVIEWZOOM_H
