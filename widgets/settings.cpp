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
    this->setWindowFlag(Qt::Dialog);
    this->setWindowTitle("Préférences");

    database = new DataBase();
    pathList = database->getSources();

    QStringListModel* model = new QStringListModel(this);
    model->setStringList(*pathList);
    ui->listRep->setModel(model);

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
