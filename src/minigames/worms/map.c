typedef struct {
	const char* name;
	size_t width;	
	size_t height;	
	unsigned x_tiles_in_viewport_num;
	unsigned y_tiles_in_viewport_num;
	int* tile_types;
	bool* is_tile_solid;
	G_SpriteComponent* map_sprite;
} G_Map;

// 48:00 for loading raw text

// make singleton for loading all assets
// map<str, SDL_Texture*> 

#include "core/game/map.h"

#include "utils/xmem.h"

// G_Map* g_map_create_random();

// map file format
// <width> <height> <tile_index> <is_solid> ... 
G_Map* g_map_create_from_file(const char* file_name, G_SpriteComponent* tile_set, const char* map_name )
{
	G_Map* map = xmalloc(sizeof(G_Map));
	for (int i = 0; i < width * height; i++) {
		map->matrix[i] = SKY;		
	}		
	map->width = width;
	map->height = height;
}

void g_map_destroy(G_Map* map)
{
	free(map->tile_types);
	free(map->is_tile_solid);
	free(map);
}

int g_map_get_tile_type(G_Map* map, int x, int y)
{
	if (x >= 0 && x < map->width && y >= 0 && y < map->height) {
		return map->tile_types[y * map->width + x];
	} else {
		return 0;			
	}
}

bool g_map_is_tile_solid(G_Map* map, int x, int y)
{
	if (x >= 0 && x < map->width && y >= 0 && y < map->height) {
		return map->is_tile_solid[y * map->width + x];
	} else {
		return true;			
	}
}
inline bool is_unit_solid(x, y);
