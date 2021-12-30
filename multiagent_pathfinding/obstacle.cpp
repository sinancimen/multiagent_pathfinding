#include "obstacle.h"

obstacle::obstacle(int identifier, QObject *parent)
    : QObject{parent}
{
    id = identifier;
}
