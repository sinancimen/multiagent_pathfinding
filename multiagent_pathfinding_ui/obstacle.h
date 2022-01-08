#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QObject>
#include "obstacle.h"
#include "map.h"

class obstacle : public QObject
{
    Q_OBJECT

private:
    int id, type, x_pos, y_pos, length, width, diameter;
    QGraphicsEllipseItem* circle;
    QGraphicsRectItem* rectangle;
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
    QGraphicsEllipseItem* getGraphicalItem_circle()
    {
        return circle;
    }
    QGraphicsRectItem* getGraphicalItem_rect()
    {
        return rectangle;
    }
    void setGraphicalItem_circle(QGraphicsEllipseItem* item)
    {
        circle = item;
    }
    void setGraphicalItem_rect(QGraphicsRectItem* item)
    {
        rectangle = item;
    }

signals:

};

#endif // OBSTACLE_H
