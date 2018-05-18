#include "core/game.h"

#include <SDL2/SDL.h>

#include <stdbool.h>

#include "common.h"
#include "utils/log.h"
#include "utils/status.h"

GAME_COLD
GAME_STATUS g_game_execute(void)
{
	SDL_Window window;
	SDL_Renderer renderer;

	GAME_STATUS init_status = game_init(&window, &renderer);

	switch (init_status) {
	GAME_STATUS_FAILURE_MAP(GAME_STATUS_EXPAND_AS_CASE)
		GAME_LOG_FATAL(
			"Unable to initialise game. Status %s\n", 
			game_status_str(init_status);
		);

		return init_status;
	default:
		break;
	}

	return game_loop();
}

GAME_COLD 
GAME_INTERNAL GAME_STATUS game_init(SDL_Window* window, SDL_Renderer* renderer)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		GAME_LOG_FATAL(
			"Unable to initialise game SDL backend: %s\n", 
			SDL_GetError()
		);	

		return FSDL2;
	}

	const char* window_title = GAME_UNAME" ["GAME_COMPILER" - x86/64]("\
								GAME_BUILD_MODE")";

	window = SDL_CreateWindow(
						window_title, 
						SDL_WINDOWPOS_UNDEFINED, 
						SDL_WINDOWPOS_UNDEFINED,
						arg_table->width->value, 
						arg_table->height->value, 
						SDL_WINDOW_RESIZABLE
					);
	
	if (window == NULL) {
		GAME_LOG_FATAL("Unable to create game window: %s\n", SDL_GetError());	
		return FSDL2;
	}

	const int DEFAULT_RENDERING_DRIVER = -1;
	renderer = SDL_CreateRenderer(
							game_window, 
							DEFAULT_RENDERING_DRIVER, 
							GAME_SDL_NO_FLAGS
						);

	if (renderer == NULL) {
		GAME_LOG_FATAL("Unable to create game renderer: %s\n", SDL_GetError());	
		return FSDL2;
	}

	return SUCCESS;
}


GAME_COLD 
GAME_INTERNAL GAME_STATUS game_loop(void)
{
	const float DESIRED_FPS = 60.0f;
	const float DESIRED_FRAME_TIME_MS = 1000.0f / DESIRED_FPS;
	const unsigned MAX_UPDATE_STEPS = 6;
	const float MAX_DELTA_TIME = 1.0f;

	for (bool game_is_running = true; !game_is_running; ) {
		for (u32 prev_ticks = SDL_GetTicks(); !game_is_running; ) {
			u32 cur_ticks = SDL_GetTicks() - prev_ticks;
			prev_ticks = cur_ticks;
			float total_delta_time = cur_ticks / DESIRED_FRAME_TIME_MS;

			GAME_STATUS handle_events_status = game_handle_events(
													window, 
													renderer
												);

			switch (handle_events_status) {
			case EXIT:
				game_is_running = false;
			GAME_STATUS_FAILURE_MAP(GAME_STATUS_EXPAND_AS_CASE)
				GAME_LOG_FATAL(
					"Unable to handle game events. Status %s\n", 
					game_status_str(handle_events_status)
				);

				game_exit();

				return handle_events_status;
			GAME_NO_DEFAULT_CASE
			}

			unsigned update_counter = 0;
			while (total_delta_time > 0.0f && update_counter < MAX_UPDATE_STEPS) {
				delta_time = G_MATH_FLOAT_MIN(total_delta_time, MAX_DELTA_TIME);
				total_delta_time -= delta_time;
				game_update(delta_time);

				++update_counter;
			}

			render();
		}
	}

	game_exit();

	return SUCCESS;
}

GAME_HOT
GAME_INTERNAL void game_update(float delta_time)
{
		
}

GAME_INTERNAL void game_render(SDL_Renderer* renderer)
{
	for (int map_x = 0; map_x < map_width; ++map_x) {
		for (int map_y = 0; map_y < map_height; ++map_y) {
			switch(map[(map_y + (int)camera_y) * map_width + (map_x + (int)camera_x)]) {
			case LAND:
				SDL_Colour colour = GREEN;
				SDL_SetRenderDrawColour(renderer, colour->r, ...);	
			case SKY:
				SDL_Colour colour = GREEN;
				SDL_SetRenderDrawColour(renderer, colour->r, ...);	
			}
			SDL_Rect render_block = {
				// ...	
			}
			SDL_FillRectDraw(renderer, render_block);
		}
	}

	for (objects_that_are_renderable) {
		obj_draw(camera_x, camera_y);
	}

	SDL_RenderPresent(renderer);
}

GAME_INTERNAL 
GAME_STATUS game_handle_events(
				SDL_Window* window, 
				SDL_Renderer* renderer
)
{
	GAME_STATUS handle_event_status = DEFAULT;

	SDL_Event event = {0};
	while (SDL_PollEvent(&event)) {
		handle_event_status = game_handle_event(event.type);

		switch (handle_event_status) {
		case EXIT:
			return EXIT;	
		GAME_STATUS_FAILURE_MAP(GAME_STATUS_EXPAND_AS_CASE)
			GAME_LOG_FATAL(
				"Unable to handle game event. Status %s\n", 
				game_status_str(handle_event_status)
			);

			return handle_event_status;
		}
	}

	return SUCCESS;
}

GAME_INTERNAL
GAME_STATUS game_handle_event(SDL_Event* event)
{
	if (event->type == SDL_QUIT) {
		return EXIT;
	} else if (event->type == SDL_WINDOWEVENT) {
		GAME_STATUS handle_window_events_status = game_handle_window_events(
														&event->window
													);
		if (handle_window_events_status !
	} else if (event->type == SDL_KEYDOWN) {
		game_handle_keyboard_events(game, &event->key);
	} else {
		return SUCCESS;		
	}
}

GAME_INTERNAL
GAME_STATUS game_handle_window_events(SDL_WindowEvent* event)
{
	switch (window_event->event) {
	case SDL_WINDOWEVENT_RESIZED:
		// ..
		break;
	case SDL_WINDOWEVENT_EXPOSED:
		game_render();
		break;

}

GAME_INTERNAL GAME_STATUS game_handle_keyboard_events(SDL_KeyboardEvent* event)
{
	// check for ctrl-q also, etc.
	switch (event->keysym.sym) {
	case SDLK_ESCAPE:
		return EXIT;
	case SDLK_W:
		create_map(map, map_width, map_height);
	}
}

GAME_INTERNAL GAME_STATUS game_handle_mouse_button_events(SDL_MouseButtonEvent* mouse_motion_event)
{
	if (event->button == SDL_BUTTON_MIDDLE) {
		add_drawable_physics_object(mouse_x + camera_x, mouse_y + camera_y);		
	}	
}

GAME_INTERNAL GAME_STATUS game_handle_mouse_motion_events(SDL_MouseMotionEvent* mouse_motion_event)
{
	float map_scroll_speed = 400.0f;
	if (event->x < 5) camera_pos_x -= map_scroll_speed * delta_time;
	if (event->x > window_width - 5) camera_pos_x += map_scroll_speed * delta_time;
	if (event->y < 5) camera_pos_y += map_scroll_speed * delta_time;
	if (event->y > window_height - 5) camera_pos_y += map_scroll_speed * delta_time;
	// must also clamp to map boundaries
}

GAME_COLD
GAME_INTERNAL void game_quit(SDL_Window* window, SDL_Renderer* renderer)
{
	if (renderer != NULL) SDL_DestroyRenderer(renderer);
	if (window != NULL) SDL_DestroyWindow(window);
	if (SDL_WasInit(SDL_INIT_EVERYTHING)) SDL_Quit();
}
