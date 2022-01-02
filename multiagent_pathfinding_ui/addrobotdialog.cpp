#include "addrobotdialog.h"
#include "ui_addrobotdialog.h"

addRobotDialog::addRobotDialog(MainWindow *parent) :
    MainWindow(),
    ui(new Ui::addRobotDialog)
{
    ui->setupUi(this);
    parentWidget = parent;
    //QObject::connect(this, SIGNAL(AddRobotClickedToMainWindow(std::vector<int>)), parent, SLOT(addRobotToList(std::vector<int>)));
}

addRobotDialog::~addRobotDialog()
{
    delete ui;
}
