#include "core/game.h"

#include <SDL2/SDL.h>

#include <stdbool.h>

#include "common.h"
#include "utils/log.h"
#include "utils/status.h"

GAME_COLD GAME_STATUS g_game_start(void)
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

	game->window = SDL_CreateWindow(
						window_title, 
						SDL_WINDOWPOS_UNDEFINED, 
						SDL_WINDOWPOS_UNDEFINED,
						arg_table->width->value, 
						arg_table->height->value, 
						SDL_WINDOW_RESIZABLE
					);
	
	if (game->window == NULL) {
		GAME_LOG_FATAL("Unable to create game window: %s\n", SDL_GetError());	
		return FSDL2;
	}

	const int DEFAULT_RENDERING_DRIVER = -1;
	game->renderer = SDL_CreateRenderer(
							game_window, 
							DEFAULT_RENDERING_DRIVER, 
							GAME_SDL_NO_FLAGS
						);

	if (game->renderer == NULL) {
		GAME_LOG_FATAL("Unable to create game renderer: %s\n", SDL_GetError());	
		return FSDL2;
	}

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
				delta_time = GAME_MIN_FLOAT(total_delta_time, MAX_DELTA_TIME);
				total_delta_time -= delta_time;
				update(delta_time);

				++update_counter;
			}

			render();
		}

		// update
		// render
	}

	game_exit();

	return SUCCESS;
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
		// bool window_is_exposed = true
		if (SDL_RenderClear(game_renderer) < 0) {
			GAME_LOG_FATAL("Unable to clear game renderer: %s\n", SDL_GetError());	
			return SDL_FAILURE;
		}
		if (SDL_RenderCopy(game_renderer, game_texture, NULL, NULL) < 0) {
			GAME_LOG_FATAL("Unable to copy to game renderer: %s\n", SDL_GetError());	
			return SDL_FAILURE;
		} 
		SDL_RenderPresent(game_renderer);
		break;

}

GAME_INTERNAL
GAME_STATUS game_handle_keyboard_events(SDL_KeyboardEvent* event)
{
	// check for ctrl-q also, etc.
	switch (event->keysym.sym) {
	case SDLK_ESCAPE:
		return EXIT;
	}
}

GAME_INTERNAL void game_quit(SDL_Window* window, SDL_Renderer* renderer)
{
	if (renderer != NULL) SDL_DestroyRenderer(renderer);
	if (window != NULL) SDL_DestroyWindow(window);
	if (SDL_WasInit(SDL_INIT_EVERYTHING)) SDL_Quit();
}
