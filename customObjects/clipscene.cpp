#include "clipscene.h"
#include <QGraphicsSceneMouseEvent>
#include <QtWidgets/QGraphicsPixmapItem>
#include <QtWidgets/QGraphicsRectItem>
#include <QDebug>
#include <QRubberBand>
#include "customObjects/resizablerubberband.h"

ClipScene::ClipScene(QObject* parent, QSize size) : QGraphicsScene(parent)
{
    windowSize = size;

}

void ClipScene::setRect(){
    selectArea = new QGraphicsRectItem();
    selectArea->setBrush(QBrush(QColor(158,182,255,96)));
    selectArea->setPen(QPen(QColor(158,182,255,200),1));
    addItem(selectArea);
    selectArea->setRect(getCurrentImageItemX(), getCurrentImageItemY(), getCurrentImageSize().rwidth(), getCurrentImageSize().rheight());

    /*rubber = new ResizableRubberBand();
    addWidget(rubber);
    rubber->setGeometry(getCurrentImageItemX(), getCurrentImageItemY(), getCurrentImageSize().rwidth(), getCurrentImageSize().rheight());
    rubber->show();
    */

    trueRubber = new QRubberBand(QRubberBand::Rectangle);
    addWidget(trueRubber);
    trueRubber->setGeometry(getCurrentImageItemX(), getCurrentImageItemY(), getCurrentImageSize().rwidth(), getCurrentImageSize().rheight());
    trueRubber->show();

    //QRubberBand *ogrubber = new QRubberBand();

}

void ClipScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{

    if(m_leftMouseButtonPressed == false){
        delete selectArea;
    }

    if (event->button() == Qt::LeftButton)
    {
        // With the left mouse button pressed, remember the position
        m_leftMouseButtonPressed = true;
        setPreviousPosition(event->scenePos());

        // Create a selection square
        selectArea = new QGraphicsRectItem();
        selectArea->setBrush(QBrush(QColor(0,0,0,0)));
        selectArea->setPen(QPen(QColor(158,182,255,200),1));
        // Add it to the graphic scene
        addItem(selectArea);
    }

    QGraphicsScene::mousePressEvent(event);
}

void ClipScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{

    if (m_leftMouseButtonPressed)
    {
        // Form the selection area when moving with the mouse while pressing the LMB
        auto dx = event->scenePos().x() - m_previousPosition.x();
        auto dy = event->scenePos().y() - m_previousPosition.y();

        if(dx < windowSize.rwidth() && dy < windowSize.rheight()){

           selectArea->setRect((dx > 0) ? m_previousPosition.x() : m_previousPosition.x() - qAbs(dx),
                           (dy > 0) ? m_previousPosition.y() : m_previousPosition.y() - qAbs(dy),
                           qAbs(event->scenePos().x() - m_previousPosition.x()) ,
                           qAbs(event->scenePos().y() - m_previousPosition.y()));
        }
      }

    QGraphicsScene::mouseMoveEvent(event);
}

void ClipScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{

    if (event->button() == Qt::LeftButton)
    {
        m_leftMouseButtonPressed = false;
        QRect selectionRect = selectArea->boundingRect().toRect();
        clippedImage(currentImageItem->pixmap().copy(selectionRect));
    }
    QGraphicsScene::mouseReleaseEvent(event);
}

void ClipScene::setPreviousPosition(const QPointF previousPosition)
{
    if (m_previousPosition == previousPosition)
        return;

    m_previousPosition = previousPosition;
    emit previousPositionChanged(m_previousPosition);
}

QPointF ClipScene::previousPosition() const
{
    return m_previousPosition;
}

void ClipScene::setImage(const QString& filePath)
{
    if (currentImageItem)
    {
        this->removeItem(currentImageItem);
    }

    currentImageItem = new QGraphicsPixmapItem(QPixmap(filePath));//.scaled(windowSize, Qt::KeepAspectRatio, Qt::SmoothTransformation)); // <------ sinon c'est moche
    addItem(currentImageItem);
}

qreal ClipScene:: getCurrentImageItemX(){
    return currentImageItem->x();
}

qreal ClipScene:: getCurrentImageItemY(){
    return currentImageItem->y();
}

QSize ClipScene:: getCurrentImageSize(){
    QPixmap p = currentImageItem->pixmap();
    return p.size();
}
