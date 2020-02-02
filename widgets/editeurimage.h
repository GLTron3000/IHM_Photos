#ifndef EDITEURIMAGE_H
#define EDITEURIMAGE_H

#include <QWidget>
#include "clipscene.h"
#include "QLabel"
#include "QSize"

namespace Ui {
class EditeurImage;
}

class EditeurImage : public QWidget
{
    Q_OBJECT

public:
    explicit EditeurImage(QWidget *parent = nullptr);
    ~EditeurImage();
    QSize getSize();
    void setImage(QString path);

private slots:
    void onClippedImage(const QPixmap& pixmap);
    void cropImageAndSave();


private:
    Ui::EditeurImage *ui;
    QImage *monImage;

    QGraphicsView* m_graphicsView;
    QLabel* m_clippedLabel;         // A label in which the cropped image will be placed
    ClipScene* m_clipScene;         // The graphical scene in which the image trimming functionality is implemented
};



#endif // EDITEURIMAGE_H
