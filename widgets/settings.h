#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QStringList>
#include "database.h"

namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

private:
    Ui::Settings *ui;
    DataBase *database;
    QStringList *pathList;
    QModelIndex indexModel;
    QStringListModel* pathModel;
    int index;


private slots:
    void addRepository();
    void end();
    void delRepository();
    void cleanDatabase();
    void destroyDatabase();
};

#endif // SETTINGS_H
