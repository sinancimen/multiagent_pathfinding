#include "addobstacledialog.h"
#include "ui_addobstacledialog.h"

addObstacleDialog::addObstacleDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addObstacleDialog)
{
    ui->setupUi(this);
}

addObstacleDialog::~addObstacleDialog()
{
    delete ui;
}
