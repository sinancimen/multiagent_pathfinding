#pragma once

#include "Node.h"
#include "robot.h"

class map : public NGraph::Graph
{
public:
	map(int width, int height);
	map(map* Map);
	tGraph<tile*> graph;
private:
	int Width;
	int Height;
	std::vector<tile*> tile_list;


public:
	tGraph<tile*> getGraph() { return graph; }
	std::vector<tile*> getTileList() { return tile_list; }
	int getWidth() { return Width; }
	int getHeight() { return Height; }
};

