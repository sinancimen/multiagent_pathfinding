#include "mainwindow.h"

void MainWindow::updateObstacleGraphics()
{
    for (int i = 0; i < obstacleList.size(); i++)
    {
        obstacle* Obstacle = obstacleList.at(i);
        std::vector<int> position = Obstacle->getPosition();
        if (Obstacle->getType())
        {
            QGraphicsEllipseItem* circle = new QGraphicsEllipseItem(position.at(0) * 20 + 10, position.at(1) * 20, Obstacle->getDiameter() * 20, Obstacle->getDiameter() * 20);
            QGraphicsEllipseItem* old_circle = Obstacle->getGraphicalItem_circle();
            circle->setBrush(QBrush(Qt::black));
            Obstacle->setGraphicalItem_circle(circle);
            scene->addItem(circle);
            scene->removeItem(old_circle);
        }
        else
        {
            QGraphicsRectItem* rectangle = new QGraphicsRectItem(position.at(0) * 20 + 10, position.at(1) * 20, Obstacle->getWidth() * 20, Obstacle->getLength() * 20);
            QGraphicsRectItem* old_rectangle = Obstacle->getGraphicalItem_rect();
            rectangle->setBrush(QBrush(Qt::black));
            Obstacle->setGraphicalItem_rect(rectangle);
            scene->addItem(rectangle);
            scene->removeItem(old_rectangle);
        }
    }
    
}

void MainWindow::updateRobotGraphics()
{
    for (int i = 0; i < robotList.size(); i++)
    {
        robot* Robot = robotList.at(i);
        std::vector<int> position = Robot->getPosition();
        std::vector<int> goal = Robot->getGoal();

        QGraphicsEllipseItem* circle = new QGraphicsEllipseItem(position.at(0) * 20 + 10, position.at(1) * 20, robot_diameter, robot_diameter);
        QGraphicsEllipseItem* old_circle = Robot->getGraphicObject();
        circle->setBrush(brushes.at(Robot->getID()));
        circle->setOpacity(1.0);
        Robot->setGraphicObject(circle);

        QGraphicsEllipseItem* circle_goal = new QGraphicsEllipseItem(goal.at(0) * 20 + 10, goal.at(1) * 20, robot_diameter, robot_diameter);
        QGraphicsEllipseItem* old_circle_goal = Robot->getGraphicObject_goal();
        circle_goal->setBrush(brushes.at(Robot->getID()));
        circle_goal->setOpacity(0.25);
        Robot->setGraphicObject_goal(circle_goal);

        scene->addItem(circle);
        scene->addItem(circle_goal);
        scene->removeItem(old_circle);
        scene->removeItem(old_circle_goal);
    }
}
