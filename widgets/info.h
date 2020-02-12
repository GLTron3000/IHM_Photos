#ifndef INFO_H
#define INFO_H

#include <QWidget>
#include <QInputDialog>
#include "widgets/explorerimg.h"
#include "widgets/note.h"
#include <QFrame>
#include <QTableWidget>
#include "starrating.h"

extern int numberOfStar;

namespace Ui {
class Info;
}

class Info : public QWidget
{
    Q_OBJECT

public:
    explicit Info(QWidget *parent = nullptr, QString imagePath =nullptr);
    ~Info();    

private slots:
    void on_ButtonEdit_clicked();

private:
    Ui::Info *ui;
    bool isVisible =false;
    QString currentImgPath;
    QString currentImgName;
    QString currentImgWxH;
    double imgWidth;
    double imgHeight;
    bool modeEdition;
    DataBase *database;
    Image *currentImage;
    QTableWidgetItem *item0;
    StarRating *starRating;



};

#endif // INFO_H
