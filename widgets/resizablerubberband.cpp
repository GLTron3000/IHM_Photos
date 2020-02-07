#include "resizablerubberband.h"
#include <QHBoxLayout>
#include <QSizeGrip>
#include <QDebug>

ResizableRubberBand::ResizableRubberBand(QWidget *parent) : QWidget(parent) {
    //setWindowFlags(Qt::SubWindow);
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    QSizeGrip* grip1 = new QSizeGrip(this);
    QSizeGrip* grip2 = new QSizeGrip(this);
    layout->addWidget(grip1, 0, Qt::AlignLeft | Qt::AlignTop);
    layout->addWidget(grip2, 0, Qt::AlignRight | Qt::AlignBottom);
    rubberband = new QRubberBand(QRubberBand::Rectangle, this);
    rubberband->move(0, 0);
    rubberband->show();
}

void ResizableRubberBand::resizeEvent(QResizeEvent *) {
    //qDebug() << "ResizeRubber "<< size();
    rubberband->resize(size());
}



//A implémenter pour bouger la selection en cliquant dessus (cf https://stackoverflow.com/questions/55307811/select-region-from-an-image-but-resizable-qrubberband-doesnt-resize)
/*void ResizableRubberBand::mousePressEvent(QMouseEvent *event){

}

void ResizableRubberBand::mouseReleaseEvent(QMouseEvent *event){

}

void ResizableRubberBand::mouseMoveEvent(QMouseEvent *event){

}
*/
