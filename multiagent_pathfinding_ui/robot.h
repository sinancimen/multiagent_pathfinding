#ifndef ROBOT_H
#define ROBOT_H

#include <QObject>
#include <QList>
#include <QGraphicsEllipseItem>
#include "tile.h"

class robot : public QObject
{
    Q_OBJECT
private:
    int id, x_pos, y_pos, x_goal, y_goal, x_goal_temp, y_goal_temp;
    int commRange;
    int detRange;
    QGraphicsEllipseItem* graphicObject;
    QGraphicsEllipseItem* graphicObject_goal;
    tile* Tile;
    std::vector<tile*> pathSequence;


public:
    explicit robot(int identifier, int communicationRange, int detectionRange, int xgoal, int ygoal, QObject *parent = nullptr);

    tile* getTile() { return Tile; }
    void setTile(tile* tile) { Tile = tile; }

    void setGraphicObject(QGraphicsEllipseItem* item)
    {
        graphicObject = item;
    }
    void setGraphicObject_goal(QGraphicsEllipseItem* item)
    {
        graphicObject_goal = item;
    }
    QGraphicsEllipseItem* getGraphicObject()
    {
        return graphicObject;
    }
    QGraphicsEllipseItem* getGraphicObject_goal()
    {
        return graphicObject_goal;
    }
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
    int getID()
    {
        return id;
    }
    int getCommunicationRange()
    {
        return commRange;
    }
    int getDetectionRange()
    {
        return detRange;
    }

    std::vector<int> getGoal()
    {
        std::vector<int> goal;
        goal.push_back(x_goal);
        goal.push_back(y_goal);
        return goal;
    }

    std::vector<int> getTempGoal()
    {
        std::vector<int> tempGoal;
        tempGoal.push_back(x_goal_temp);
        tempGoal.push_back(y_goal_temp);
        return tempGoal;
    }

    void setTempGoal(int xpos, int ypos)
    {
        x_goal_temp = xpos;
        y_goal_temp = ypos;
    }

    void setPath(std::vector<tile*> path) { pathSequence = path; }
    tile* getNextStep() 
    {
        tile* next_step;
        if (pathSequence.size())
        {
            next_step = pathSequence.front();
        }
        else
        {
            next_step = Tile;
        }
        return next_step; 
    }

    std::vector<tile*> getPath() { return pathSequence; }

    void takeStep()
    {
        Tile = pathSequence.at(0);
        x_pos = Tile->x_pos;
        y_pos = Tile->y_pos;
        pathSequence.erase(pathSequence.begin());
    }

    

signals:

};


#endif // ROBOT_H


