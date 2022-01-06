#pragma once

#include "tile.h"

class Node
{
public:
	Node(tile* Tile, Node* parent, int manhattan_distance)
	{
		m_parent = parent;
		m_tile = Tile;
		ManhattanDistance = manhattan_distance;
	}
	tile* m_tile;
	Node* m_parent;
	int ManhattanDistance;
};

