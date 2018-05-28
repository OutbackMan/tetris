#include "core/events.h"

#include <SDL2/SDL.h>

G_HOT
void g_events_handle(G_Game* game)
{
	SDL_assert(game != NULL);

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			events_handle_quit(game);
			break;
		case SDL_WINDOWEVENT:
			events_handle_window(game, &event.window);
			break;
		case SDL_KEYDOWN:
			events_handle_key_down(game, &event.key);
			break;
		case SDL_KEYUP:
			events_handle_key_up(game, &event.key);
			break;
		case SDL_MOUSEBUTTONDOWN:
			events_handle_mouse_down(game, &event.button);
			break;
		case SDL_MOUSEBUTTONUP:
			events_handle_mouse_up(game, &event.button);
			break;
		case SDL_MOUSEMOTION:
			events_handle_mouse_motion(game, &event.motion);
			break;
		}
	}
}

G_INTERNAL
void events_handle_quit(G_Game* game)
{
	SDL_assert(game != NULL);

	game->want_to_run = false;	
}

G_INTERNAL
void events_handle_window(G_Game* game, SDL_WindowEvent* window_event)
{
	SDL_assert(game != NULL);
	SDL_assert(window_event != NULL);

	switch (window_event->type) {
	case SDL_WINDOWEVENT_RESIZED:
	case SDL_WINDOWEVENT_SIZE_CHANGED:
		game->window->width = window_event->data1;
		game->window->height = window_event->data2;
		break;
	case SDL_WINDOWEVENT_EXPOSED:
		game->window->is_exposed = true;
		break;
	}

}

#define IS_KEY_DOWN_QUIT_KEY(keyboard_event) \
	((keyboard_event->keysym.sym == SDLK_q \
	&& keyboard_event->keysym.mod == KMOD_CTRL) \
	|| keyboard_event->keysym.sym == SDLK_ESCAPE)
G_INTERNAL void events_handle_key_down(G_Game* game, SDL_KeybordEvent* keyboard_event)
{
	SDL_assert(game != NULL);
	SDL_assert(keyboard_event != NULL);

	if (IS_KEY_DOWN_QUIT_KEY(keyboard_event)) {
		game->want_to_run = false;
	}
	
	if (keyboard_event->keysym.sym == SDLK_w && !keyboard_event->repeat)
		g_map_create(game->map, game->map->width, game->map->height);
	}

	if (keyboard_event->keysym.sym == SDLK_x)
	// jump
		physics_system_jump_left(entity_manager);
		entity_manager->physics[entity_under_control].is_stable;
				object_under_control->vx = +4.0f;		
				object_under_control->vy = -8.0f;		
				object_under_control->is_stable = false;		
			}	
		}
	case SDLK_z:
	// jump
		if (object_under_control != NULL) {
			if (object_under_control->is_stable) {
				object_under_control->vx = -4.0f;		
				object_under_control->vy = -8.0f;		
				object_under_control->is_stable = false;		
			}	
		}
	case SDLK_A_IS_HELD:
	object_under_control->shoot_angle -= 1.0f * delta_time;
	case SDLK_SPACE:
	energising = true;
	energy_level = 0.0f;
	case SDLK_SPACE_IS_HELD:
	if (energising) {
		energy_level += 0.75f * delta_time;
		if (energy_level >= 1.0f) {
			energy_level = 1.0f;		
		}
	}
	case SDLK_SPACE_IS_RELEASED:
	fire_weapon = true;
	energising = false;

	}
}
#undef IS_KEY_DOWN_QUIT_KEY

G_INTERNAL void events_handle_key_up(G_Game* game, SDL_KeybordEvent* keyboard_event)
{
	SDL_assert(game != NULL);
	SDL_assert(keyboard_event != NULL);

	
}

G_INTERNAL void events_handle_mouse_down(SDL_MouseButtonEvent* mouse_button_event)
{
	SDL_assert(game != NULL);
	SDL_assert(mouse_button_event != NULL);

	if (event->button == SDL_BUTTON_MIDDLE) {
		// create PHYSICS | RENDERABLE component
		add_drawable_physics_object(mouse_x + camera_x, mouse_y + camera_y);		
	}

	if (event->button == SDL_BUTTON_LEFT) {
		add_20_debris_objects(mouse_x + camera_x, mouse_y + camera_y);
		// append to list of game objects
	}
}

G_INTERNAL void events_handle_mouse_up(SDL_MouseButtonEvent* mouse_button_event)
{
	SDL_assert(game != NULL);
	SDL_assert(mouse_button_event != NULL);

}

G_INTERNAL void events_handle_mouse_motion(SDL_MouseMotionEvent* mouse_motion_event)
{
	SDL_assert(game != NULL);
	SDL_assert(mouse_motion_event != NULL);

	float map_scroll_speed = 400.0f;
	if (event->x < 5) camera_pos_x -= map_scroll_speed * delta_time;
	if (event->x > window_width - 5) camera_pos_x += map_scroll_speed * delta_time;
	if (event->y < 5) camera_pos_y += map_scroll_speed * delta_time;
	if (event->y > window_height - 5) camera_pos_y += map_scroll_speed * delta_time;
	// must also clamp to map boundaries
}
