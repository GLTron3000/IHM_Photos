#include "settings.h"
#include "ui_settings.h"

#include <QPushButton>
#include <QFileDialog>
#include <QListView>
#include <QStringListModel>

Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    QStringList list;

    connect(ui->pbRep, &QPushButton::pressed, this, &Settings::addRepository);
    connect(ui->pbEnd, &QPushButton::pressed, this, &Settings::end);


}

Settings::~Settings()
{
    delete ui;
}

void Settings::addRepository(){

    QStringListModel* model = new QStringListModel(this);
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    QString outputFolder = QFileDialog::getExistingDirectory(0, ("Select Output Folder"), QDir::currentPath());
    if(outputFolder != nullptr){
        list.append((outputFolder));
        model->setStringList(list);
        ui->listRep->setModel(model);
    }
}

void Settings::end(){
    this->close();
}
