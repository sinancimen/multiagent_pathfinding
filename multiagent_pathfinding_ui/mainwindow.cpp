#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::AddRobotClicked()
{
    m_addRobotWidget = new addRobotDialog;
    m_addRobotWidget->show();
}

void MainWindow::AddObstacleClicked()
{
    m_addObstacleWidget = new addObstacleDialog;
    m_addObstacleWidget->show();
}


void MainWindow::addToObstacleList(obstacle* obstacle_)
{
    obstacleList->push_back(obstacle_);
}
void MainWindow::clearObstacleList()
{
    obstacleList->clear();
}
QList<obstacle*> MainWindow::getObstacleList()
{
    return *obstacleList;
}

void MainWindow::addRobotToList(robot* robot_)
{
    robotList->push_back(robot_);
}
void MainWindow::clearRobotList()
{
    robotList->clear();
}
QList<robot*> MainWindow::getRobotList()
{
    return *robotList;
}
