#pragma once

#include "map.h"

int calculateHeuristic_Manhattan(tile* Tile, int goal_x, int goal_y);
std::vector<Node*> successors(Node* node, map* Map, robot* Robot);

struct CompareManhattanDistance
{
    bool operator()(Node* const& n1, Node* const& n2)
    {
        return n1->ManhattanDistance > n2->ManhattanDistance;
    }
};
