#pragma once

#include "tile.h"
class map : public NGraph::Graph
{
public:
	map(int width, int height);
private:
	int Width;
	int Height;
	tGraph<tile*> graph;
	std::vector<tile*> tile_list;


public:
	tGraph<tile*> getGraph() { return graph; }
	std::vector<tile*> getTileList() { return tile_list; }
};
