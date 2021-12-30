#ifndef ROBOT_H
#define ROBOT_H

#include <QObject>

class robot : public QObject
{
    Q_OBJECT
private:
    int id, x_pos, y_pos;
    int commRange;
    int detRange;
public:
    explicit robot(int identifier, int communicationRange, int detectionRange, QObject *parent = nullptr);
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

signals:

};

#endif // ROBOT_H
