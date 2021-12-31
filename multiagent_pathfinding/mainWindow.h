#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "addrobotdialog.h"
#include "addobstacledialog.h"

class QPushButton;
class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    QPushButton *m_AddRobotButton;
    QPushButton *m_AddObstacleButton;
    addRobotDialog *m_AddRobotDialog;
    addObstacleDialog *m_AddObstacleDialog;

signals:

};

#endif // MAINWINDOW_H
