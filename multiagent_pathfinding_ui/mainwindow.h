#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "addrobotdialog.h"
#include "addobstacledialog.h"
#include "robot.h"
#include "obstacle.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    addRobotDialog *m_addRobotWidget;
    addObstacleDialog *m_addObstacleWidget;

    QList<robot*> *robotList;
    QList<obstacle*> *obstacleList;

public:


public slots:
    void AddRobotClicked();
    void AddObstacleClicked();

    void addToObstacleList(obstacle* obstacle_);
    void clearObstacleList();
    QList<obstacle*> getObstacleList();

    void addRobotToList(robot* robot_);
    void clearRobotList();
    QList<robot*> getRobotList();
};
#endif // MAINWINDOW_H
