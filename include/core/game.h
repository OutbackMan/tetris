#ifndef __core_game_h__
#define __core_game_h__

#include "common.h"

GAME_COLD
GAME_STATUS g_game_execute(void);

// renderable
typedef struct {
	SDL_Texture* texture; // sprite
	size_t texture_width;
	size_t texture_height;
} Renderable;

// physics
typedef struct {
	float px; // move into renderable
	float py; // move into renderable
	float vx;
	float vy;
	float ax;
	float ay;
	float collision_radius;
	float friction;
	bool is_stable;
	int bounce_before_death;
	bool is_dead;
} PhysicsObject;

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
