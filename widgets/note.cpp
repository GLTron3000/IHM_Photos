#include "note.h"
#include "ui_note.h"
#include <QApplication>
#include <QTableWidget>

#include "stardelegate.h"
#include "stareditor.h"
#include "starrating.h"
#include "QDebug"

Note::Note(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Note)
{
    ui->setupUi(this);
    ui->note->setRowCount(1);
    ui->note->setColumnCount(1);
    ui->note->setItemDelegate(new StarDelegate);
    ui->note->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    ui->note->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->note->setHorizontalHeaderLabels({"Note"});

    static constexpr struct {int rating;}
    staticData[] = {{0}};
    QTableWidgetItem *item0 = new QTableWidgetItem;
    item0->setData(0,QVariant::fromValue(StarRating(staticData[0].rating)));
    ui->note->setItem(0, 0, item0);

    ui->note->resizeColumnToContents(this->size().rwidth());
    /*QTableWidget tableWidget(1,1);
    tableWidget.setItemDelegate(new StarDelegate);
    tableWidget.setEditTriggers(QAbstractItemView::DoubleClicked
                                | QAbstractItemView::SelectedClicked);
    tableWidget.setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget.setHorizontalHeaderLabels({"Rating"});

    populateTableWidget(&tableWidget);

    tableWidget.resizeColumnsToContents();
    tableWidget.resize(500, 300);
    tableWidget.show();*/

}

Note::~Note()
{
    delete ui;
}
