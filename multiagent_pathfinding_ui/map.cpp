#include "map.h"

map::map(int width, int height)
{
	Width = width;
	Height = height;
	for (int i = 0; i < Width; i++)
	{
		for (int j = 0; j < Height; j++)
		{
			tile* Tile = new tile(i, j);
			tile_list.push_back(Tile);
			graph.insert_vertex(Tile);
		}
	}

	for (int k=0; k < tile_list.size(); k++)
	{
		tile* Tile = tile_list.at(k);
		if (Tile->x_pos < Width - 1)
		{
			if (Tile->x_pos != 0)
			{
				graph.insert_edge(Tile, tile_list.at(k + Height));
				graph.insert_edge(Tile, tile_list.at(k - Height));
			}
			else
			{
				graph.insert_edge(Tile, tile_list.at(k + Height));
			}
		}
		else
		{
			graph.insert_edge(Tile, tile_list.at(k - Height));
		}

		if (Tile->y_pos < Height - 1)
		{
			if (Tile->y_pos != 0)
			{
				graph.insert_edge(Tile, tile_list.at(k + 1));
				graph.insert_edge(Tile, tile_list.at(k - 1));
			}
			else
			{
				graph.insert_edge(Tile, tile_list.at(k + 1));
			}
		}
		else
		{
			graph.insert_edge(Tile, tile_list.at(k - 1));
		}
	}
}