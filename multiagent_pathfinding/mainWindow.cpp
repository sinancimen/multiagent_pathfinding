#include "mainWindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QWidget{parent}
{
    setFixedSize(500, 500);
    setWindowTitle("Multiagent Pathfinding");
    m_AddRobotButton = new QPushButton("Add Robot", this);
    m_AddRobotButton->setGeometry(10, 10, 80, 20);
    m_AddObstacleButton = new QPushButton("Add Obstacle", this);
    m_AddObstacleButton->setGeometry(100, 10, 80, 20);
    m_AddRobotDialog = new addRobotDialog();
    m_AddObstacleDialog = new addObstacleDialog();

    connect(m_AddRobotButton, SIGNAL(clicked()), m_AddRobotDialog, SLOT(show()));
    connect(m_AddObstacleButton, SIGNAL(clicked()), m_AddObstacleDialog, SLOT(show()));
}
