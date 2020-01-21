#ifndef EXPLORER_H
#define EXPLORER_H

#include <QMainWindow>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class Explorer; }
QT_END_NAMESPACE

class Explorer : public QMainWindow
{
    Q_OBJECT

public:
    Explorer(QWidget *parent = nullptr);
    ~Explorer();
    QStandardItemModel *model;

private:
    Ui::Explorer *ui;
    void loadFiles();
};

#endif // EXPLORER_H
