#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <queue>
#include <functional>
#include <math.h>
#include <iostream>
#include "helpers.h"


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

    Map = new map(480, 480);
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
    std::vector<tile*> tileList = Map->getTileList();
    for (unsigned int i = 0; i < tileList.size(); i++)
    {
        if ((tileList.at(i)->x_pos = Robot->getPosition().at(0)) && (tileList.at(i)->y_pos = Robot->getPosition().at(1)))
        {
            Robot->setTile(tileList.at(i));
            break;
        }
    }
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


void MainWindow::localRepairAStar_Solver()
{
    for (int i = 0; i < robotList.size(); i++)
    {
        map* MapClone(Map);
        robot* robot_considered = robotList.at(i);
        std::set<tile*> neighbour_tiles = MapClone->getGraph().out_neighbors(robot_considered->getTile());
        for (tile* Tile : neighbour_tiles)
        {
            for (int k = 0; k < robotList.size(); k++)
            {
                if (Tile == robotList.at(k)->getTile())
                {
                    MapClone->getGraph().remove_edge(Tile, robotList.at(k)->getTile());
                }
            }
            localRepairAStar_Search(robot_considered);
        }
    }

}

void MainWindow::localRepairAStar_Search(robot* Robot)
{
    map* MapClone(Map);
    std::priority_queue<Node*, std::vector<Node*>, CompareManhattanDistance> queue;
    Node* initialNode = new Node(Robot->getTile(), NULL, calculateHeuristic_Manhattan(Robot->getTile(), Robot->getGoal().at(0), Robot->getGoal().at(1)));
    queue.push(initialNode);
    Node* result = NULL;
    std::vector<tile*> labeled_tiles;
    bool duplicate = false;

    while (true)
    {
        std::vector<Node*> successors_list = successors(queue.top(), MapClone, Robot);
        Node* node_temp = queue.top();
        labeled_tiles.push_back(queue.top()->m_tile);

        if (queue.top()->m_tile->x_pos == Robot->getGoal().at(0) && queue.top()->m_tile->y_pos == Robot->getGoal().at(1))
        {
            result = queue.top();
            break;
        }
        queue.pop();

        for (unsigned int i = 0; i < successors_list.size(); i++)
        {
            duplicate = false;
            for (unsigned int j = 0; j < labeled_tiles.size(); j++)
            {
                if (labeled_tiles.at(j) == successors_list.at(i)->m_tile)
                {
                    duplicate = true;
                }
            }
            if (!duplicate)
                queue.push(successors_list.at(i));
        }
    }

    std::vector<tile*> resultSequence;
    resultSequence.push_back(result->m_tile);
    Node* parentNode = result->m_parent;
    while (parentNode != NULL)
    {
        resultSequence.insert(resultSequence.begin(), parentNode->m_tile);
        parentNode = parentNode->m_parent;
    }
    resultSequence.erase(resultSequence.begin());
    Robot->setPath(resultSequence);
}

