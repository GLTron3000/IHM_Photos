#ifndef GRAPHICSVIEWZOOM_H
#define GRAPHICSVIEWZOOM_H

#include <QObject>
#include <QGraphicsView>

class GraphicsViewZoom : public QGraphicsView
{
    Q_OBJECT


public:
    explicit GraphicsViewZoom(QWidget *parent = 0);

private:
    qreal _numScheduledScalings = 0;
    QPoint wheelEventMousePos;

public slots:
    void wheelEvent(QWheelEvent* event);
    void scalingTime(qreal x);
    void animFinished();

signals:

};

#endif // GRAPHICSVIEWZOOM_H
