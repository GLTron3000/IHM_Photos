#include "info.h"
#include "ui_info.h"
#include <QInputDialog>

Info::Info(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Info)
{
    ui->setupUi(this);
    //on_keyWordsButton_clicked();
}

Info::~Info()
{
    delete ui;
}

void Info::on_keyWordsButton_clicked()
{
    QString Kwords = QInputDialog::getText(this, "#Tags", "Entrer le(s) mot(s)-clé(s):");
    ui->valueKeyWordsLabel->setText(Kwords);
}
