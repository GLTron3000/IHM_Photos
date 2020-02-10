#include "settings.h"
#include "ui_settings.h"

#include <QPushButton>
#include <QFileDialog>
#include <QListView>
#include <QStringListModel>
#include <QDebug>
#include <QMessageBox>


Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::Dialog);
    this->setWindowTitle("Préférences");

    database = new DataBase();
    pathList = database->getSources();

    pathModel = new QStringListModel(this);
    pathModel->setStringList(*pathList);
    ui->listRep->setModel(pathModel);

    connect(ui->pbRep, SIGNAL(pressed()), this, SLOT(addRepository()));
    connect(ui->pbEnd, SIGNAL(pressed()), this, SLOT(end()));
    connect(ui->pbSup, SIGNAL(pressed()), this, SLOT(delRepository()));
    connect(ui->pushButtonNuke, SIGNAL(pressed()), this, SLOT(destroyDatabase()));
    connect(ui->pushButtonClean, SIGNAL(pressed()), this, SLOT(cleanDatabase()));
}

Settings::~Settings()
{
    delete ui;
}

void Settings::addRepository(){
    pathModel = new QStringListModel(this);
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);

    QString outputFolder = QFileDialog::getExistingDirectory(0, ("Ajouter une nouvelle source"), QDir::currentPath());

    qDebug() << "NOUVELLE SOURCE";

    if(outputFolder != nullptr){
        pathList->append((outputFolder));
        pathModel->setStringList(*pathList);
        ui->listRep->setModel(pathModel);
        qDebug() << "   +" << outputFolder;
        database->addSource(outputFolder);
    }
}

void Settings::end(){
    this->close();
}

void Settings::delRepository(){
    qDebug() << "REMOVE REPO SELECTION";
    QModelIndexList selected = ui->listRep->selectionModel()->selectedIndexes();
    if (!selected.isEmpty()){
        qDebug() << "   +REMOVED " << selected.first().row();
        QString path = pathModel->data(selected.first()).toString();
        database->deleteSource(path);
        pathModel->removeRow(selected.first().row());
    }
}

void Settings::cleanDatabase(){
    ui->pushButtonClean->setDisabled(true);
    database->cleaner();
    ui->pushButtonClean->setDisabled(false);
}

void Settings::destroyDatabase(){
    int ret = QMessageBox::critical(this, tr("Supprimer toutes les données ?"),
                                   tr("Cette action supprimera tous les albums.\n"
                                      "Etes vous sur ?"),
                                   QMessageBox::Yes | QMessageBox::No,
                                   QMessageBox::Yes);
    if(ret == QMessageBox::Yes){
        database->clear();
    }
}
