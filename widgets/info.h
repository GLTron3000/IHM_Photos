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

private slots:
    void on_keyWordsButton_clicked();

private:
    Ui::Info *ui;
};

#endif // INFO_H
