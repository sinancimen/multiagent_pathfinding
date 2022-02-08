#include "mainwindow.h"
#include "helpers.h"

std::vector<int> MainWindow::whcAStar_Solver(robot* robot_considered)
{

    map* MapClone = new map(Map);
    std::set<tile*> neighbour_tiles = MapClone->getGraph().out_neighbors(robot_considered->getTile());
    std::vector<int> results;
    for (tile* Tile : neighbour_tiles)
    {
        for (int k = 0; k < robotList.size(); k++)
        {
            if (Tile == robotList.at(k)->getTile())
            {
                MapClone->graph.remove_edge(Tile, robotList.at(k)->getTile());
            }
        }
    }
    localRepairAStar_Search(robot_considered, MapClone);
    results = whcAStar_Search(robot_considered, MapClone);
    return results;
}

std::vector<int> MainWindow::whcAStar_Search(robot* Robot, map* MapClone)
{
    std::priority_queue<TimedNode*, std::vector<TimedNode*>, CompareManhattanDistanceTimed> queue;
    Node* initialNode = new Node(Robot->getTile(), NULL, calculateHeuristic_Manhattan(Robot->getTile(), Robot->getTempGoal().at(0), Robot->getTempGoal().at(1)));
    TimedNode* initialTimedNode = new TimedNode(Robot->getTile(), NULL, calculateHeuristic_Manhattan(Robot->getTile(), Robot->getTempGoal().at(0), Robot->getTempGoal().at(1)), 0);
    if (Robot->getPath().size() > window)
    {
        Robot->setTempGoal(Robot->getPath().at(window - 1)->x_pos, Robot->getPath().at(window - 1)->y_pos);
    }
    else
    {
        Robot->setTempGoal(Robot->getGoal().at(0), Robot->getGoal().at(1));
    }
    queue.push(initialTimedNode);
    TimedNode* result = NULL;
    std::vector<tile*> labeled_tiles;
    std::vector<int> labeled_times;
    bool duplicate = false;

    while (true)
    {
        std::vector<TimedNode*> successors_list = timedSuccessors_whca(queue.top(), MapClone, Robot, reservationTable);
        TimedNode* node_temp = queue.top();
        labeled_tiles.push_back(node_temp->m_tile);
        labeled_times.push_back(node_temp->time);

        if (node_temp->time >= window)
        {
            node_temp->isGoal = true;
            result = node_temp;
            break;
        }
        queue.pop();

        for (unsigned int i = 0; i < successors_list.size(); i++)
        {
            duplicate = false;
            for (unsigned int j = 0; j < labeled_tiles.size(); j++)
            {
                if (labeled_tiles.at(j) == successors_list.at(i)->m_tile && labeled_times.at(j) == successors_list.at(i)->time)
                {
                    duplicate = true;
                }
            }
            if (!duplicate)
                queue.push(successors_list.at(i));
        }
    }

    std::vector<tile*> resultSequence;
    resultSequence.push_back(result->m_tile);
    reservationTable.push_back(result);
    TimedNode* parentNode = result->m_parent;
    int moves = 0;
    while (parentNode != NULL)
    {
        resultSequence.insert(resultSequence.begin(), parentNode->m_tile);
        reservationTable.push_back(parentNode);
        if (parentNode->m_parent != NULL)
        {
            if (parentNode->m_tile != parentNode->m_parent->m_tile)
            {
                moves += 1;
            }
        }

        parentNode = parentNode->m_parent;
    }
    resultSequence.erase(resultSequence.begin());
    Robot->setPath(resultSequence);
    std::vector<int> results;
    results.push_back(result->time);
    results.push_back(moves);
    return results;
}

//void MainWindow::whcAStar_setGoals()
//{
//    for (int i = 0; i < robotList.size(); i++)
//    {
//        int x_pos = robotList.at(i)->getPosition().at(0);
//        int y_pos = robotList.at(i)->getPosition().at(1);
//        int x_goal = robotList.at(i)->getGoal().at(0);
//        int y_goal = robotList.at(i)->getGoal().at(1);
//        int x_diff = abs(x_pos - x_goal);
//        int y_diff = abs(y_pos - y_goal)
//        if (x_diff + y_diff <= window)
//        {
//            robotList.at(i)->setTempGoal(x_goal, y_goal);
//        }
//        else
//        {
//            if (x_diff >= window / 2 && y_diff >= window / 2)
//            {
//                robotList.at(i)->setTempGoal((x_pos + x_goal) / 2, (y_pos + y_goal) / 2);
//            }
//            else if (x_diff >= window / 2)
//            {
//
//            }
//        }
//    }
//}

//bool compareHeuristic(robot* r1, robot* r2)
//{
//    return (calculateHeuristic_Manhattan(r1->getTile(), r1->getGoal().at(0), r1->getGoal().at(1)) < calculateHeuristic_Manhattan(r1->getTile(), r1->getGoal().at(0), r1->getGoal().at(1)));
//}

struct compareHeuristic
{
    bool operator()(robot* r1, robot* r2)
    {
        return (calculateHeuristic_Manhattan(r1->getTile(), r1->getGoal().at(0), r1->getGoal().at(1)) > calculateHeuristic_Manhattan(r2->getTile(), r2->getGoal().at(0), r2->getGoal().at(1)));
    }
};


void MainWindow::whcAStar_doOrdering()
{
    std::sort(robotList.begin(), robotList.end(), compareHeuristic());
}



bool MainWindow::checkForStatus()
{
    bool finished = true;
    for (int i = 0; i < robotList.size(); i++)
    {
        if ((robotList.at(i)->getPosition().at(0) != robotList.at(i)->getGoal().at(0)) || (robotList.at(i)->getPosition().at(1) != robotList.at(i)->getGoal().at(1)))
        {
            finished = false;
            break;
        }
    }
    return finished;
}

