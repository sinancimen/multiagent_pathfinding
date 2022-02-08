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
		if (parent == NULL)
		{
			depth = 0;
		}
		else
		{
			depth = parent->depth + 1;
		}
	}
	tile* m_tile;
	Node* m_parent;
	int ManhattanDistance;
	int depth;
};

