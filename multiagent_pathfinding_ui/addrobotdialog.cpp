#include "addrobotdialog.h"
#include "ui_addrobotdialog.h"

addRobotDialog::addRobotDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addRobotDialog)
{
    ui->setupUi(this);
}

addRobotDialog::~addRobotDialog()
{
    delete ui;
}
