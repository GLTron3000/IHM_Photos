#ifndef INFO_H
#define INFO_H

#include <QWidget>
#include <QInputDialog>
#include "widgets/explorer.h"

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

};

#endif // INFO_H
