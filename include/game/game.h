#ifndef __core_game_game_h__
#define __core_game_game_h__

#include "common.h"


typedef struct {
	bool want_to_run;	
	// current_map
	G_Window* window;
	G_Renderer* renderer;
	G_Camera* camera;
	G_Players* players;
	G_Map* map;
	G_EntityManager* entity_manager;
} G_Game;

void g_game_destroy(G_Game* game);

GAME_COLD
GAME_STATUS g_game_execute(void);

typedef struct {
	SDL_Window* window;
	size_t width;
	size_t height;
	bool is_exposed; // use to determine if to display pause screen
} G_GameWindow;

typedef struct {
	SDL_Renderer* renderer;	
} G_GameRenderer;




// ai
// determine angle formed from parabolic trajectory relating to range and elevation

typedef struct {
	Renderable* members;	
} GroupRenderable;
/*
	bool is_team_dead = false;
	for (team_member) {
		is_team_dead |= team_member->is_alive;	
	}
	return is_team_dead;
*/


// renderable
typedef struct {
	SDL_Texture* texture; // sprite
	size_t texture_width;
	size_t texture_height;
	unsigned width_scale;
	unsigned height_scale;
} Renderable;

void physics_object_create(obj, x, y)
{
	obj->px = x;
	obj->py = y;
	obj->collision_radius = 4.0f;
	obj->is_stable = false;
	obj->friction = 0.8f;
	obj->is_dead = false
	obj->bounce_before_death = -1;
}

// use this as you would an object create routine
void boom(x, y, explosion_radius)
{
	// shockwave other entities
	for (all_drawable_objects) {
		float dx = obj->px - x;
		float dy = obj->py - y;
		float dist = sqrt(dx*dx + dy*dy);

		if (dist < explosion_radius) {
			obj->vx = (dx / dist) * radius;	
			obj->vy = (dy / dist) * radius;	
			obj->is_stable = false;
		}
	}	

	for (int i = 0; i < (int)radius; ++i) {
		drawable_objects.push(create_object);		
	}
}

void create_example_object(obj, x, y)
{
	obj->vx = 10.0f * cosf((float)rand() / (float)RAND_MAX * 2.0f * PI);
	obj->vy = 10.0f * sinf((float)rand() / (float)RAND_MAX * 2.0f * PI);
	obj->radius = 1.0f;
	obj->friction = 1.2f;
	obj->bounce_before_death = 5;
}

void physics_object_draw(obj)
{
	SDL_Rect src = {
		.x = 0,
		.y = 0
		.w = sprite_width,
		.h = sprite_height
	};

	SDL_Rect dst = {
		.x = obj->x + sprite_width - camera_offset_x,
		.y = obj->y + sprite_height - camera_offset_y,
		.w = sprite_width, // with respect to window dimensions
		.h = sprite_height,
	};

	float rotation = atan2f(obj->vx, obj->vy);

	SDL_RenderCopyEx(renderer, sprite, src, dst, rotation, NULL, SDL_FLIP_NONE);
}


#endif
