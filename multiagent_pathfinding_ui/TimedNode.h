#pragma once

#include "Node.h"

class TimedNode
{
public:
	TimedNode(tile* Tile, TimedNode* parent, int manhattan_distance, int Time)
	{
		m_parent = parent;
		m_tile = Tile;
		time = Time;
		manhattanDistance = manhattan_distance;
	}
	tile* m_tile;
	TimedNode* m_parent;
	int manhattanDistance;
	int time;
	bool isGoal = false;
};