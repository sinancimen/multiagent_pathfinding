#include "helpers.h"

int calculateHeuristic_Manhattan(tile* Tile, int goal_x, int goal_y)
{
    return (abs(Tile->x_pos - goal_x) + abs(Tile->y_pos - goal_y));
}

std::vector<Node*> successors(Node* node, map* Map, robot* Robot)
{
    std::set<tile*> adj_set = Map->getGraph().out_neighbors(node->m_tile);
    std::vector<Node*> adj_vec;
    for (tile* Tile : adj_set)
    {
        Node* nd = new Node(Tile, node, calculateHeuristic_Manhattan(Tile, Robot->getGoal().at(0), Robot->getGoal().at(1)));
        adj_vec.push_back(nd);
    }
    return adj_vec;
}

std::vector<TimedNode*> timedSuccessors(TimedNode* node, map* Map, robot* Robot, std::vector<TimedNode*> reservationTable)
{
    std::set<tile*> adj_set = Map->getGraph().out_neighbors(node->m_tile);
    adj_set.insert(node->m_tile);
    std::vector<TimedNode*> adj_vec;
    bool occupied = false;
    for (tile* Tile : adj_set)
    {
        occupied = false;
        for (int i = 0; i < reservationTable.size(); i++)
        {
            if (reservationTable.at(i)->m_tile == Tile && (reservationTable.at(i)->time == node->time + 1 || (reservationTable.at(i)->time == node->time) || (reservationTable.at(i)->isGoal && reservationTable.at(i)->time < node->time + 1)))
            {
                occupied = true;
            }
        }
        if (!occupied)
        {
            TimedNode* nd = new TimedNode(Tile, node, calculateHeuristic_Manhattan(Tile, Robot->getGoal().at(0), Robot->getGoal().at(1)) * 2 + node->time + 1, node->time + 1);
            adj_vec.push_back(nd);
        }
    }
    return adj_vec;
}


