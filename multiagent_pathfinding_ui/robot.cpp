#include "robot.h"

robot::robot(int identifier, int communicationRange, int detectionRange, int xgoal, int ygoal, QObject *parent)
    : QObject{parent}
{
    id = identifier;
    commRange = communicationRange;
    detRange = detectionRange;
    x_goal = xgoal;
    y_goal = ygoal;
}
