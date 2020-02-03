#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QStringList>

namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT
    QStringList list;

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

private:
    Ui::Settings *ui;


private slots:
    void addRepository();
    void end();
};

#endif // SETTINGS_H
