#ifndef VISIONNEUSE_H
#define VISIONNEUSE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Visionneuse; }
QT_END_NAMESPACE

class Visionneuse : public QMainWindow
{
    Q_OBJECT

public:
    Visionneuse(QWidget *parent = nullptr);
    ~Visionneuse();

private:
    Ui::Visionneuse *ui;
};

#endif // VISIONNEUSE_H
