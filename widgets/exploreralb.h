#ifndef EXPLORERALB_H
#define EXPLORERALB_H

#include <QWidget>

namespace Ui {
class ExplorerAlb;
}

class ExplorerAlb : public QWidget
{
    Q_OBJECT

public:
    explicit ExplorerAlb(QWidget *parent = nullptr);
    ~ExplorerAlb();

private:
    Ui::ExplorerAlb *ui;
};

#endif // EXPLORERALB_H
