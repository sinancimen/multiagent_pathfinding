#pragma once

#include "tile.h"
#include "Node.h"

int calculateHeuristic_Manhattan(tile* Tile, int goal_x, int goal_y)
{
	return (abs(Tile->x_pos - goal_x) + abs(Tile->y_pos - goal_y));
}

struct CompareManhattanDistance
{
    bool operator()(Node* const& n1, Node* const& n2)
    {
        return n1->ManhattanDistance > n2->ManhattanDistance;
    }
};

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