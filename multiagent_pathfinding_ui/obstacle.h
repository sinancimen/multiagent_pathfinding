#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QObject>
#include "obstacle.h"

class obstacle : public QObject
{
    Q_OBJECT

private:
    int id, x_pos, y_pos;
public:
    explicit obstacle(int identifier, QObject *parent = nullptr);
    std::vector<int> getPosition()
    {
        std::vector<int> position;
        position.push_back(x_pos);
        position.push_back(y_pos);
        return position;
    }
    void setPosition(int xpos, int ypos)
    {
        x_pos = xpos;
        y_pos = ypos;
    }

signals:

};

#endif // OBSTACLE_H
