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

    QPointF rubberPosOld = mapToScene(rubber->pos());

    auto targetViewportPos = event->pos();
    auto targetScenePos = mapToScene(event->pos());

    scale(factor, factor);
    centerOn(targetScenePos);
    QPointF deltaViewportPos = targetViewportPos - QPointF(viewport()->width() / 2.0, viewport()->height() / 2.0);
    QPointF viewportCenter = mapFromScene(targetScenePos) - deltaViewportPos;
    centerOn(mapToScene(viewportCenter.toPoint()));

    if(cropActive){
        QSize rubberSize = rubber->size() * factor;
        rubber->resize(rubberSize);
        rubber->move(mapFromScene(rubberPosOld));
    }
}

void GraphicsViewZoom::scaleAll(double factor){
    QPointF rubberPosOld = mapToScene(rubber->pos());
    scale(factor, factor);
    if(cropActive){
        QSize rubberSize = rubber->size() * factor;
        rubber->resize(rubberSize);
        rubber->move(mapFromScene(rubberPosOld));
    }
}

QPixmap GraphicsViewZoom::getRubberSelection(){
    QPointF rubberPos = mapToScene(rubber->pos());
    QSize rubberSize = rubber->size();

    QRectF selection = QRectF(rubberPos, rubberSize);

    QPixmap pixmap(selection.size().toSize());
    QPainter painter(&pixmap);
    this->scene()->render(&painter, QRectF(), selection);

    return pixmap;
}

void GraphicsViewZoom::initCrop(){
    cropActive = false;
    this->rubber = new QRubberBand(QRubberBand::Rectangle, this);
    this->rubber->setGeometry(QRect(-1, -1, 2, 2));
}

bool GraphicsViewZoom::cropMode(){
    cropActive = cropActive ? false : true;
    if(cropActive){
        this->setDragMode(QGraphicsView::NoDrag);
        initialDrag = true;
        QApplication::setOverrideCursor(Qt::CrossCursor);
    }else{
        this->setDragMode(QGraphicsView::ScrollHandDrag);
        rubber->setGeometry(QRect(-1, -1, 2, 2));
        rubber->hide();
        initialDrag = false;
        QApplication::restoreOverrideCursor();
    }

    return cropActive;
}

void GraphicsViewZoom::mousePressEvent(QMouseEvent *event){
    if(cropActive){
        rubberOrigin = event->pos();
        rubber->setGeometry(QRect(rubberOrigin, QSize()));
        rubberDrag = true;
        rubber->show();
    }
    QGraphicsView::mousePressEvent(event);
}

void GraphicsViewZoom::mouseMoveEvent(QMouseEvent *event){
    if(cropActive && rubberDrag){
        rubberEnd = event->pos();
        rubber->setGeometry(QRect(rubberOrigin, rubberEnd).normalized());
        rubber->show();
    }
    QGraphicsView::mouseMoveEvent(event);
}

void GraphicsViewZoom::mouseReleaseEvent(QMouseEvent *event){
    if(cropActive){
        rubberEnd = event->pos();
        rubber->setGeometry(QRect(rubberOrigin, rubberEnd).normalized());
        rubberDrag = false;
    }
    QGraphicsView::mouseReleaseEvent(event);
}

