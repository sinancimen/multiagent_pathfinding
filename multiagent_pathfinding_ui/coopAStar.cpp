#include "mainwindow.h"
#include "helpers.h"

void MainWindow::coopAStar_Solver(robot* robot_considered)
{
    
    map* MapClone = new map(Map);
    std::set<tile*> neighbour_tiles = MapClone->getGraph().out_neighbors(robot_considered->getTile());
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
    coopAStar_Search(robot_considered, MapClone);
}

void MainWindow::coopAStar_Search(robot* Robot, map* MapClone)
{
    std::priority_queue<TimedNode*, std::vector<TimedNode*>, CompareManhattanDistanceTimed> queue;
    Node* initialNode = new Node(Robot->getTile(), NULL, calculateHeuristic_Manhattan(Robot->getTile(), Robot->getGoal().at(0), Robot->getGoal().at(1)));
    TimedNode* initialTimedNode = new TimedNode(Robot->getTile(), NULL, calculateHeuristic_Manhattan(Robot->getTile(), Robot->getGoal().at(0), Robot->getGoal().at(1)), 0);
    queue.push(initialTimedNode);
    TimedNode* result = NULL;
    std::vector<tile*> labeled_tiles;
    std::vector<int> labeled_times;
    bool duplicate = false;

    while (true)
    {
        std::vector<TimedNode*> successors_list = timedSuccessors(queue.top(), MapClone, Robot, reservationTable);
        TimedNode* node_temp = queue.top();
        labeled_tiles.push_back(node_temp->m_tile);
        labeled_times.push_back(node_temp->time);

        if (node_temp->m_tile->x_pos == Robot->getGoal().at(0) && node_temp->m_tile->y_pos == Robot->getGoal().at(1))
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
    while (parentNode != NULL)
    {
        resultSequence.insert(resultSequence.begin(), parentNode->m_tile);
        reservationTable.push_back(parentNode);
        parentNode = parentNode->m_parent;
    }
    resultSequence.erase(resultSequence.begin());
    Robot->setPath(resultSequence);
}