#include "obstacle.h"

obstacle::obstacle(int identifier, int obstype, int posx, int posy, int len, int width_, int dia, QObject *parent)
    : QObject{parent}
{
    id = identifier;
    type = obstype;
    x_pos = posx;
    y_pos = posy;
    length = len;
    width = width_;
    diameter = dia;
}
