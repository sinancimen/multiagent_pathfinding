#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    view = ui->graphicsView;
    scene = new QGraphicsScene(this);
    scene->setSceneRect(20,10, 480, 480);
    ui->graphicsView->setScene(scene);
    brushes.push_back(QBrush(Qt::green));
    brushes.push_back(QBrush(Qt::red));
    brushes.push_back(QBrush(Qt::yellow));
    brushes.push_back(QBrush(Qt::magenta));
    brushes.push_back(QBrush(Qt::cyan));
    brushes.push_back(QBrush(Qt::darkGreen));
    brushes.push_back(QBrush(Qt::darkYellow));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addToObstacleList()
{
    obstacle* Obstacle = new obstacle(1, getObstacleType(), getPositionX_obs().toInt(), getPositionY_obs().toInt(), getLength_obs().toInt(), getWidth_obs().toInt(), getDiameter_obs().toInt());
    obstacleList.append(Obstacle);
    drawObstacle(Obstacle);
}
void MainWindow::clearObstacleList()
{
    obstacleList.clear();
}
QList<obstacle*> MainWindow::getObstacleList()
{
    return obstacleList;
}

void MainWindow::addRobotToList()
{
    int identity;
    if (robotList.size() > 0)
    {
        identity = robotList.at(robotList.size() - 1)->getID() + 1;
    }
    else
    {
        identity = 0;
    }
    robot* Robot = new robot(identity, getCommRange().toInt(), getDetRange().toInt(), getGoalX().toInt(), getGoalY().toInt());
    Robot->setPosition(getPositionX().toInt(), getPositionY().toInt());
    QGraphicsEllipseItem* circle = new QGraphicsEllipseItem(getPositionX().toInt()+10, getPositionY().toInt(), robot_diameter, robot_diameter);
    circle->setBrush(brushes.at(identity));
    Robot->setGraphicObject(circle);
    robotList.append(Robot);
    updateRobotGraphics();
}
void MainWindow::clearRobotList()
{
    robotList.clear();
}
QList<robot*> MainWindow::getRobotList()
{
    return robotList;
}
void MainWindow::drawObstacle(obstacle* Obstacle)
{
    std::vector<int> position = Obstacle->getPosition();
    if (Obstacle->getType())
    {
        QGraphicsEllipseItem* circle = new QGraphicsEllipseItem(position.at(0)+10, position.at(1), Obstacle->getDiameter(), Obstacle->getDiameter());
        circle->setBrush(QBrush(Qt::black));
        scene->addItem(circle);
    }
    else
    {
        QGraphicsRectItem* rectangle = new QGraphicsRectItem(position.at(0)+10, position.at(1), Obstacle->getWidth(), Obstacle->getLength());
        rectangle->setBrush(QBrush(Qt::black));
        scene->addItem(rectangle);
    }
}

void MainWindow::updateRobotGraphics()
{
    for (int i=0; i<robotList.size(); i++)
    {
        robot* Robot = robotList.at(i);
        std::vector<int> position = Robot->getPosition();
        QGraphicsEllipseItem* circle = new QGraphicsEllipseItem(position.at(0)+10, position.at(1), robot_diameter, robot_diameter);
        QGraphicsEllipseItem* old_circle = Robot->getGraphicObject();
        circle->setBrush(brushes.at(Robot->getID()));
        Robot->setGraphicObject(circle);
        scene->addItem(circle);
        scene->removeItem(old_circle);
    }
}
