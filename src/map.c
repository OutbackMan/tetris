#include "map.h"

G_Map* g_map_create(unsigned width, unsigned height, unsigned tile_width, unsigned tile_height)
{
	
}

int g_map__get_tile(int x, int y)
{
	if (x >= 0 && x < map_width && y >= 0 && y < map_height) {
		return map[y * map_width + x];		
	} else {
		// error		
	}	
}

void g_map_render(G_Map* map, G_Camera* camera, SDL_Renderer* renderer)
{
	int field_width;
	int field_height;

	SDL_RenderGetLogicalSize(renderer, &field_width, &field_height);

	int visible_tiles_x = field_width / map->tile_width;
	int visible_tiles_y = field_height / map->tile_height;

	float offset_x = camera->x - (float)visible_tiles_x / 2.0f; 
	float offset_y = camera->y - (float)visible_tiles_y / 2.0f; 

	// clamping ...
	if (offset_x < 0) offset_x = 0.0f;
	if (offset_y < 0) offset_y = 0.0f;

	SDL_Rect tile_draw;

	for (int map_x = 0; map_x < visible_tiles_x; ++x) {
		for (int map_y = 0; map_y < visible_tiles_y; ++y) {
			int tile_id = g_map__get_tile(x, y);

			tile_draw =  {
				.x = x * map->tile_width,
				.y = y * map->tile_height,
				.w = (x + 1) * map->tile_width,
				.h = (y + 1) * map->tile_height
			};
	
			switch (tile_id) {
			case SKY:
				SDL_Render(
			}
		}	
	}
}
