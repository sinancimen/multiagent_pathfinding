#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "robot.h"
#include "obstacle.h"
#include <QWidget>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QBrush>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString getPositionX() { return position_x;}
    QString getPositionY() { return position_y;}
    QString getGoalX() { return goal_x;}
    QString getGoalY() { return goal_y;}
    QString getCommRange() { return commRange;}
    QString getDetRange() { return detRange;}
    QString getPositionX_obs() { return position_x_obs;}
    QString getPositionY_obs() { return position_y_obs;}
    QString getLength_obs() { return length_obs;}
    QString getWidth_obs() { return width_obs;}
    QString getDiameter_obs() {return diameter_obs;}
    int getObstacleType() {return obstacleIndex;}



private:
    Ui::MainWindow *ui;

    QList<robot*> robotList;
    QList<obstacle*> obstacleList;

    QString position_x;
    QString position_y;
    QString goal_x;
    QString goal_y;
    QString commRange;
    QString detRange;

    int obstacleIndex;
    QString position_x_obs;
    QString position_y_obs;
    QString length_obs;
    QString width_obs;
    QString diameter_obs;
    void drawObstacle(obstacle* Obstacle);
    QGraphicsView* view;
    QGraphicsScene* scene;
    void updateRobotGraphics();
    int robot_diameter = 10;
    QList<QBrush> brushes;


public:


public slots:

    void addToObstacleList();
    void clearObstacleList();
    QList<obstacle*> getObstacleList();

    void addRobotToList();
    void clearRobotList();
    QList<robot*> getRobotList();

    void setPositionX(QString position)
    {
        position_x = position;
    }
    void setPositionY(QString position)
    {
        position_y = position;
    }
    void setGoalX(QString goal)
    {
        goal_x = goal;
    }
    void setGoalY(QString goal)
    {
        goal_y = goal;
    }
    void setCommRange(QString range)
    {
        commRange = range;
    }
    void setDetRange(QString range)
    {
        detRange = range;
    }

    void setPositionX_obs(QString position)
    {
        position_x_obs = position;
    }
    void setPositionY_obs(QString position)
    {
        position_y_obs = position;
    }
    void setObstacleIndex(int index)
    {
        obstacleIndex = index;
    }
    void setWidth_obs(QString width)
    {
        width_obs = width;
    }
    void setLength_obs(QString length)
    {
        length_obs = length;
    }
    void setDiameter_obs(QString diameter)
    {
        diameter_obs = diameter;
    }
};
#endif // MAINWINDOW_H
