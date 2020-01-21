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
    QStandardItemModel *imagesModel;

public:
    Explorer(QWidget *parent = nullptr);
    ~Explorer();
    void loadImages();

private slots:
    void reload();
    void quit();

private:
    Ui::Explorer *ui;

private:
    void loadPath(QString path);
    void loadThumbs();
};

#endif // EXPLORER_H
