#include "settings.h"
#include "ui_settings.h"

#include <QPushButton>
#include <QFileDialog>
#include <QListView>
#include <QStringListModel>
#include <QDebug>


Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::Dialog);
    this->setWindowTitle("Préférences");

    database = new DataBase();
    pathList = database->getSources();

    QStringListModel* model = new QStringListModel(this);
    model->setStringList(*pathList);
    ui->listRep->setModel(model);

    connect(ui->pbRep, &QPushButton::pressed, this, &Settings::addRepository);
    connect(ui->pbEnd, &QPushButton::pressed, this, &Settings::end);
    connect(ui->listRep, SIGNAL(clicked(const QModelIndex)), this, SLOT(leftClick(QModelIndex)));
    connect(ui->pbSup, SIGNAL(pressed()), this, SLOT(delRepository()));
    ui->pbSup->setDisabled(true);

}

Settings::~Settings()
{
    delete ui;
}

void Settings::addRepository(){
    QStringListModel* model = new QStringListModel(this);
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);

    QString outputFolder = QFileDialog::getExistingDirectory(0, ("Ajouter une nouvelle source"), QDir::currentPath());

    qDebug() << "NOUVELLE SOURCE";

    if(outputFolder != nullptr){
        pathList->append((outputFolder));
        model->setStringList(*pathList);
        ui->listRep->setModel(model);
        qDebug() << "   +" << outputFolder;
        database->addSource(outputFolder);
    }
}

void Settings::end(){
    this->close();
}

void Settings::leftClick(QModelIndex i){

    ui->pbSup->setDisabled(false);
    index = i.row();
}


void Settings::delRepository(){

    if(ui->listRep->model()->removeRow(index))
        qDebug() << "Removed \n";

    else
        qDebug() << "Fail \n";


    database->deleteSource(index);
    ui->listRep->update();
    ui->pbSup->setDisabled(true);

}
