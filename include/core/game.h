#ifndef __core_game_h__
#define __core_game_h__

#include "common.h"

GAME_COLD
GAME_STATUS g_game_execute(void);


// physics
typedef struct {
	float px;
	float py;
	float vx;
	float vy;
	float ax;
	float ay;
	float collision_radius;
	bool is_stable;
} PhysicsObject;

void physics_object_create(obj, x, y)
{
	obj->px = x;
	obj->py = y;
	obj->collision_radius = 4.0f;
	obj->is_stable = false;
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
