#include "mainwindow.h"
#include "helpers.h"


void MainWindow::localRepairAStar_Solver(robot* robot_considered)
{
    map* MapClone(Map);
    std::set<tile*> neighbour_tiles = MapClone->getGraph().out_neighbors(robot_considered->getTile());
    for (tile* Tile : neighbour_tiles)
    {
        for (int k = 0; k < robotList.size(); k++)
        {
            if (Tile == robotList.at(k)->getTile())
            {
                MapClone->getGraph().remove_edge(Tile, robotList.at(k)->getTile());
            }
        }
    }
    localRepairAStar_Search(robot_considered);
}

void MainWindow::localRepairAStar_Search(robot* Robot)
{
    map* MapClone(Map);
    std::priority_queue<Node*, std::vector<Node*>, CompareManhattanDistance> queue;
    Node* initialNode = new Node(Robot->getTile(), NULL, calculateHeuristic_Manhattan(Robot->getTile(), Robot->getGoal().at(0), Robot->getGoal().at(1)));
    queue.push(initialNode);
    Node* result = NULL;
    std::vector<tile*> labeled_tiles;
    bool duplicate = false;

    while (true)
    {
        std::vector<Node*> successors_list = successors(queue.top(), MapClone, Robot);
        Node* node_temp = queue.top();
        labeled_tiles.push_back(node_temp->m_tile);

        if (node_temp->m_tile->x_pos == Robot->getGoal().at(0) && node_temp->m_tile->y_pos == Robot->getGoal().at(1))
        {
            result = node_temp;
            break;
        }
        queue.pop();

        for (unsigned int i = 0; i < successors_list.size(); i++)
        {
            duplicate = false;
            for (unsigned int j = 0; j < labeled_tiles.size(); j++)
            {
                if (labeled_tiles.at(j) == successors_list.at(i)->m_tile)
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
    Node* parentNode = result->m_parent;
    while (parentNode != NULL)
    {
        resultSequence.insert(resultSequence.begin(), parentNode->m_tile);
        parentNode = parentNode->m_parent;
    }
    resultSequence.erase(resultSequence.begin());
    Robot->setPath(resultSequence);
}
