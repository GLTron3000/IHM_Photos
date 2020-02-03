#ifndef GRAPHICSVIEWZOOM_H
#define GRAPHICSVIEWZOOM_H

#include <QObject>
#include <QGraphicsView>
#include "customObjects/resizablerubberband.h"
#include <QRubberBand>

class GraphicsViewZoom : public QGraphicsView
{
    Q_OBJECT


public:
    explicit GraphicsViewZoom(QWidget *parent = 0);
    void initCrop();
    QRubberBand *rubber;
    ResizableRubberBand *rubberR;

private:
    qreal _numScheduledScalings = 0;
    QPoint wheelEventMousePos;
    QPoint rubberOrigin;
    QPoint rubberEnd;
    bool rubberDrag;
    bool cropActive;

public slots:
    void wheelEvent(QWheelEvent* event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void cropMode();
    void scalingTime(qreal x);
    void animFinished();

signals:

};

#endif // GRAPHICSVIEWZOOM_H
