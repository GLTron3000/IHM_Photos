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

private slots:

    void on_ButtonEdit_clicked();

    void on_ButtonValider_clicked();

private:
    Ui::Info *ui;
    bool isVisible =false;
    QString imgPath;


};

#endif // INFO_H
