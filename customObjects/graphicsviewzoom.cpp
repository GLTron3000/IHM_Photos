#include "graphicsviewzoom.h"
#include <QWheelEvent>
#include <QTimeLine>
#include <QDebug>

GraphicsViewZoom::GraphicsViewZoom(QWidget *parent) : QGraphicsView(parent){
    setTransformationAnchor(QGraphicsView::NoAnchor);
    setResizeAnchor(QGraphicsView::NoAnchor);
    setDragMode(QGraphicsView::ScrollHandDrag);
}

void GraphicsViewZoom::wheelEvent(QWheelEvent* event){
    wheelEventMousePos = event->pos();

    int numDegrees = event->delta() / 8;
    int numSteps = numDegrees / 15; // see QWheelEvent documentation
    _numScheduledScalings += numSteps;
    if (_numScheduledScalings * numSteps < 0) // if user moved the wheel in another direction, we reset previously scheduled scalings
        _numScheduledScalings = numSteps;

    QTimeLine *anim = new QTimeLine(350, this);
    anim->setUpdateInterval(20);

    connect(anim, SIGNAL (valueChanged(qreal)), SLOT (scalingTime(qreal)));
    connect(anim, SIGNAL (finished()), SLOT (animFinished()));
    anim->start();
 }

void GraphicsViewZoom::scalingTime(qreal x){
    QPointF oldPos = mapToScene(wheelEventMousePos);

    qreal factor = 1.0+ qreal(_numScheduledScalings) / 300.0;
    scale(factor, factor);

    qDebug() << "SCALE " << factor;
    QSize rubberSize = rubberR->size();
    rubberSize.scale(factor, factor, Qt::KeepAspectRatio);
    rubberR->resize(rubberSize);

    QPointF newPos = mapToScene(wheelEventMousePos);
    QPointF delta = newPos - oldPos;
    this->translate(delta.x(), delta.y());

}

void GraphicsViewZoom::animFinished()
{
    if (_numScheduledScalings > 0)
        _numScheduledScalings--;
    else
        _numScheduledScalings++;

    sender()->~QObject();
}

void GraphicsViewZoom::initCrop(){
    cropActive = false;
    rubberR = new ResizableRubberBand(this);
    //this->scene()->addWidget(rubber);
    rubberR->setGeometry(QRect(-1, -1, 2, 2));
}

void GraphicsViewZoom::cropMode(){
    cropActive = cropActive ? false : true;
    if(cropActive){
        this->setDragMode(QGraphicsView::NoDrag);
        rubberR->show();
    }else{
        this->setDragMode(QGraphicsView::ScrollHandDrag);
        rubberR->setGeometry(QRect(-1, -1, 2, 2));
        rubberR->hide();
    }
}

void GraphicsViewZoom::mousePressEvent(QMouseEvent *event){
    if(cropActive){
        rubberOrigin = this->mapToScene(event->pos()).toPoint();
        rubberR->setGeometry(QRect(rubberOrigin, QSize()));
        rubberDrag = true;
        rubberR->show();
    }
    QGraphicsView::mousePressEvent(event);
}

void GraphicsViewZoom::mouseMoveEvent(QMouseEvent *event){
    if(cropActive && rubberDrag){
        rubberEnd = this->mapToScene(event->pos()).toPoint();
        rubberR->setGeometry(QRect(rubberOrigin, rubberEnd).normalized());
        rubberR->show();
    }
    QGraphicsView::mouseMoveEvent(event);
}

void GraphicsViewZoom::mouseReleaseEvent(QMouseEvent *event){
    if(cropActive){
        rubberEnd = this->mapToScene(event->pos()).toPoint();
        rubberR->setGeometry(QRect(rubberOrigin, rubberEnd).normalized());
        rubberDrag = false;
    }
    QGraphicsView::mouseReleaseEvent(event);
}

