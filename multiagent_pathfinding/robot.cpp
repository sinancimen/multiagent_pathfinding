#include "robot.h"

robot::robot(int identifier, int communicationRange, int detectionRange, QObject *parent)
    : QObject{parent}
{
    id = identifier;
    commRange = communicationRange;
    detRange = detectionRange;
}
