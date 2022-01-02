#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QObject>
#include "obstacle.h"

class obstacle : public QObject
{
    Q_OBJECT

private:
    int id, type, x_pos, y_pos, length, width, diameter;
public:
    explicit obstacle(int identifier, int obstype, int posx, int posy, int len, int width_, int dia, QObject *parent = nullptr);
    std::vector<int> getPosition()
    {
        std::vector<int> position;
        position.push_back(x_pos);
        position.push_back(y_pos);
        return position;
    }
    int getType()
    {
        return type;
    }
    int getLength()
    {
        return length;
    }
    int getWidth()
    {
        return width;
    }
    int getDiameter()
    {
        return diameter;
    }

signals:

};

#endif // OBSTACLE_H
