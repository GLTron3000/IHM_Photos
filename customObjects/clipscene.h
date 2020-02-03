#ifndef CLIPSCENE_H
#define CLIPSCENE_H

#include <QtWidgets/QGraphicsScene>
#include "customObjects/resizablerubberband.h"
#include <QRubberBand>

class QGraphicsSceneMouseEvent;
class QGraphicsPixmapItem;
class QGraphicsRectItem;

class clipscene
{
public:
    clipscene();
};

class ClipScene : public QGraphicsScene
{
    Q_OBJECT
    Q_PROPERTY(QPointF previousPosition READ previousPosition WRITE setPreviousPosition NOTIFY previousPositionChanged)

public:
    ClipScene(QObject* parent, QSize size);
    QGraphicsPixmapItem* currentImageItem {nullptr};
    ResizableRubberBand *rubber;
    QRubberBand* trueRubber;
    QPointF previousPosition() const;
    // Method for replacing an image in QGraphicsScene
    void setImage(const QString& filePath);
    qreal getCurrentImageItemX();
    qreal getCurrentImageItemY();
    QSize getCurrentImageSize();

    void setRect();
    void crop();
    void resize();

signals:
    void previousPositionChanged(const QPointF previousPosition);
    void clippedImage(const QPixmap& pixmap);  // A signal that transmits the cut out area to the application window to install it in the label

public slots:
    void setPreviousPosition(const QPointF previousPosition);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;


private:
    QGraphicsRectItem* selectArea          {nullptr};
    QPointF m_previousPosition;
    bool m_leftMouseButtonPressed           {false};
    QSize windowSize;
    QSize imageSize; //taille de l'image à cropp.
    bool cropMode;
    bool resizeMode;
};


#endif // CLIPSCENE_H
