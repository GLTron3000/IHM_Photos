#include "graphicsviewzoom.h"
#include <QWheelEvent>
#include <QTimeLine>
#include <QDebug>
#include <QtMath>
#include <QApplication>

GraphicsViewZoom::GraphicsViewZoom(QWidget *parent) : QGraphicsView(parent){
    setTransformationAnchor(QGraphicsView::NoAnchor);
    setResizeAnchor(QGraphicsView::NoAnchor);
    setDragMode(QGraphicsView::ScrollHandDrag);
}

void GraphicsViewZoom::wheelEvent(QWheelEvent* event){
    double angle = event->angleDelta().y();
    double factor = qPow(1.0015, angle);

    QPointF rubberPosOld = mapToScene(rubberR->pos());

    auto targetViewportPos = event->pos();
    auto targetScenePos = mapToScene(event->pos());

    scale(factor, factor);
    centerOn(targetScenePos);
    QPointF deltaViewportPos = targetViewportPos - QPointF(viewport()->width() / 2.0, viewport()->height() / 2.0);
    QPointF viewportCenter = mapFromScene(targetScenePos) - deltaViewportPos;
    centerOn(mapToScene(viewportCenter.toPoint()));

    if(cropActive){
        QSize rubberSize = rubberR->size() * factor;
        rubberR->resize(rubberSize);
        rubberR->move(mapFromScene(rubberPosOld));
    }
}

void GraphicsViewZoom::scaleAll(double factor){
    QPointF rubberPosOld = mapToScene(rubberR->pos());
    scale(factor, factor);
    if(cropActive){
        QSize rubberSize = rubberR->size() * factor;
        rubberR->resize(rubberSize);
        rubberR->move(mapFromScene(rubberPosOld));
    }
}

void GraphicsViewZoom::initCrop(ResizableRubberBand *rubber){
    cropActive = false;
    rubberR = rubber;
    rubberR->setGeometry(QRect(-1, -1, 2, 2));
}

bool GraphicsViewZoom::cropMode(){
    cropActive = cropActive ? false : true;
    if(cropActive){
        this->setDragMode(QGraphicsView::NoDrag);
        initialDrag = true;
        QApplication::setOverrideCursor(Qt::CrossCursor);
    }else{
        this->setDragMode(QGraphicsView::ScrollHandDrag);
        rubberR->setGeometry(QRect(-1, -1, 2, 2));
        rubberR->hide();
        initialDrag = false;
        QApplication::restoreOverrideCursor();
    }

    return cropActive;
}

void GraphicsViewZoom::mousePressEvent(QMouseEvent *event){
    if(cropActive && initialDrag){
        rubberOrigin = event->pos();
        rubberR->setGeometry(QRect(rubberOrigin, QSize()));
        rubberDrag = true;
        rubberR->show();
    }
    QGraphicsView::mousePressEvent(event);
}

void GraphicsViewZoom::mouseMoveEvent(QMouseEvent *event){
    if(cropActive && initialDrag && rubberDrag){
        rubberEnd = event->pos();
        rubberR->setGeometry(QRect(rubberOrigin, rubberEnd).normalized());
        rubberR->show();
    }
    QGraphicsView::mouseMoveEvent(event);
}

void GraphicsViewZoom::mouseReleaseEvent(QMouseEvent *event){
    if(cropActive && initialDrag){
        rubberEnd = event->pos();
        rubberR->setGeometry(QRect(rubberOrigin, rubberEnd).normalized());
        rubberDrag = false;
        initialDrag = false;
        QApplication::restoreOverrideCursor();
    }
    QGraphicsView::mouseReleaseEvent(event);
}

