#include "settings.h"
#include "ui_settings.h"

#include <QToolBar>
#include <QVBoxLayout>

Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{

    auto tb = new QToolBar();
    tb->addAction("1");
    tb->addAction("2");

    auto dockLayout = new QVBoxLayout(); //or any other layout type you want
    dockLayout->setMenuBar(tb); // <-- the interesting part

    auto dockContent = new QWidget();
    dockContent->setLayout(dockLayout);

    //yourDockWidget->setWidget(dockContent);

    ui->setupUi(this);

}

Settings::~Settings()
{
    delete ui;
}
