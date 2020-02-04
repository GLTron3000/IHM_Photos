#ifndef EXPLORERALB_H
#define EXPLORERALB_H

#include <QWidget>

namespace Ui {
class explorerAlb;
}

class explorerAlb : public QWidget
{
    Q_OBJECT

public:
    explicit explorerAlb(QWidget *parent = nullptr);
    ~explorerAlb();

private:
    Ui::explorerAlb *ui;
};

#endif // EXPLORERALB_H
