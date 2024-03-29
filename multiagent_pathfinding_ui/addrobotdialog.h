#ifndef ADDROBOTDIALOG_H
#define ADDROBOTDIALOG_H

#include <QWidget>
#include "robot.h"
#include "mainwindow.h"

namespace Ui {
class addRobotDialog;
}

class addRobotDialog : public MainWindow
{
    Q_OBJECT

public:
    explicit addRobotDialog(MainWindow *parent = nullptr);
    ~addRobotDialog();
    QString getPositionX() { return position_x;}
    QString getPositionY() { return position_y;}
    QString getGoalX() { return goal_x;}
    QString getGoalY() { return goal_y;}
    QString getCommRange() { return commRange;}
    QString getDetRange() { return detRange;}



private:
    Ui::addRobotDialog *ui;
    QString position_x;
    QString position_y;
    QString goal_x;
    QString goal_y;
    QString commRange;
    QString detRange;
    MainWindow* parentWidget;

public slots:
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
    void AddRobotClickedToMainWindow()
    {
        std::vector<int> params;
        params.push_back(getCommRange().toInt());
        params.push_back(getDetRange().toInt());
        params.push_back(getGoalX().toInt());
        params.push_back(getGoalY().toInt());
        params.push_back(getPositionX().toInt());
        params.push_back(getPositionY().toInt());
        parentWidget->addRobotToList(params);
    }
};

#endif // ADDROBOTDIALOG_H
