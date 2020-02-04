#ifndef INFO_H
#define INFO_H

#include <QWidget>
#include <QInputDialog>

namespace Ui {
class Info;
}

class Info : public QWidget
{
    Q_OBJECT

public:
    explicit Info(QWidget *parent = nullptr);
    ~Info();
    void setImgPath(QString imgpath);
    void setW(double width);
    void setH(double height);
    void setInfos();

private slots:

    void on_ButtonEdit_clicked();

    void on_ButtonValider_clicked();

private:
    Ui::Info *ui;
    bool isVisible =false;
    QString imgPath;
    double imgWidth;
    double imgHeight;
    bool modeEdition;

};

#endif // INFO_H
