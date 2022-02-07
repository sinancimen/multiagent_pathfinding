#pragma once

#include "map.h"
#include "TimedNode.h"

int calculateHeuristic_Manhattan(tile* Tile, int goal_x, int goal_y);
std::vector<Node*> successors(Node* node, map* Map, robot* Robot);
std::vector<TimedNode*> timedSuccessors(TimedNode* node, map* Map, robot* Robot, std::vector<TimedNode*> reservationTable);

struct CompareManhattanDistance
{
    bool operator()(Node* const& n1, Node* const& n2)
    {
        return n1->ManhattanDistance > n2->ManhattanDistance;
    }
};

struct CompareManhattanDistanceTimed
{
    bool operator()(TimedNode* const& n1, TimedNode* const& n2)
    {
        return n1->manhattanDistance > n2->manhattanDistance;
    }
};


