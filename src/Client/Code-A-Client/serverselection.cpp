#include "serverselection.h"
#include "ui_serverselection.h"

serverselection::serverselection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::serverselection)
{
    ui->setupUi(this);
}

serverselection::~serverselection()
{
    delete ui;
}
