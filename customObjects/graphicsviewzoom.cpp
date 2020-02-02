#include "graphicsviewzoom.h"
#include <QWheelEvent>
#include <QTimeLine>

GraphicsViewZoom::GraphicsViewZoom(QWidget *parent) : QGraphicsView(parent){
    setTransformationAnchor(QGraphicsView::NoAnchor);
    setResizeAnchor(QGraphicsView::NoAnchor);
}

void GraphicsViewZoom::wheelEvent(QWheelEvent* event)
{
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

void GraphicsViewZoom::scalingTime(qreal x)
{
    QPointF oldPos = mapToScene(wheelEventMousePos);

    qreal factor = 1.0+ qreal(_numScheduledScalings) / 300.0;
    scale(factor, factor);

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
