#include "core/game.h"

#include <SDL2/SDL.h>

#include <stdbool.h>

#include "common.h"
#include "utils/log.h"
#include "utils/status.h"

GAME_STATUS g_game_start(void)
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

	GAME_STATUS handle_events_status = DEFAULT;
	for (bool game_is_running = true; !game_is_running; ) {
		handle_events_status = game_handle_events(window, renderer);

		switch (handle_events_status) {
		case EXIT:
			game_is_running = false;
		case FAILURE:
			GAME_LOG_FATAL(
				"Unable to handle game events. Status %s\n", 
				game_status_str(handle_events_status)
			);

			return FAILURE;
		}
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
		handle_event_status = game_handle_event(game, event.type);

		switch (handle_event_status) {
		case EXIT:
			return EXIT;	
		case FAILURE:
		case FSDL2:
			GAME_LOG_FATAL(
				"Unable to handle game event. Status %s\n", 
				game_status_str(handle_event_status)
			);

			return FAILURE;
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
														game, 
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
GAME_STATUS game_handle_window_events(Game* game, SDL_Event* event)
{
}

GAME_INTERNAL
GAME_STATUS game_handle_keyboard_events(Game* game, SDL_Event* event)
{
}

GAME_INTERNAL GAME_STATUS handle_keyboard_events(Game* game, SDL_KeyboardEvent* keyboard_event)
{
	// check for ctrl-q also, etc.
	switch (keyboard_event->keysym.sym) {
		
	}
	if (event.key.keysym.sym == SDLK_ESCAPE) {
		game->is_running = false;
	} else {
		game__system_input(game, event);
	}
	
}

GAME_INTERNAL GAME_STATUS handle_window_events(Game* game, SDL_WindowEvent* window_event)
{
	switch (window_event->event) {
	case SDL_WINDOWEVENT_RESIZED:
		if (game_texture_resize(game->texture, game->renderer, window_event.data1, window_event.data2) != SUCCESS) {
			GAME_LOG_FATAL("Unable to resize game texture: %s\n", SDL_GetError());	
			return SDL_FAILURE;
		}
		break;
	case SDL_WINDOWEVENT_EXPOSED:
		if (game_convert_field_to_texture() < 0) {
			GAME_LOG_FATAL("Unable to update game texture: %s\n", SDL_GetError());	
			return SDL_FAILURE;
		}
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

GAME_INTERNAL void game_quit(SDL_Window* window, SDL_Renderer* renderer)
{
	if (renderer != NULL) SDL_DestroyRenderer(renderer);
	if (window != NULL) SDL_DestroyWindow(window);
	if (SDL_WasInit(SDL_INIT_EVERYTHING)) SDL_Quit();
}
