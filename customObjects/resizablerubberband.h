#ifndef RESIZABLERUBBERBAND_H
#define RESIZABLERUBBERBAND_H

#include <QWidget>
#include <QRubberBand>

class ResizableRubberBand : public QWidget
{
    Q_OBJECT
public:
    explicit ResizableRubberBand(QWidget *parent = nullptr);

private:
    QRubberBand* rubberband;
    void resizeEvent(QResizeEvent *);

signals:

};

#endif // RESIZABLERUBBERBAND_H
