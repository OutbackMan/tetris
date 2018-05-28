#include "game/game.h"

#include <SDL2/SDL.h>

#include <stdbool.h>
#include <stdlib.h>

#include "common.h"
#include "camera.h"
#include "map.h"
#include "players.h"
#include "loop.h"
#include "utils/error.h"
#include "utils/sdl-wrappers.h"
#include "utils/xmem.h"

inline void g_game_exit(int exit_status)
{
	SDL_Quit();
	exit(exit_status);
}

G_COLD 
void g_game_execute(void)
{
	G_Game* game = game_create();
	if (game == NULL) {
		SDL_LogCritical(
			SDL_LOG_CATEGORY_APPLICATION, 
			"Unable to create game instance %s", 
			g_error_get()
		);
		return;
	} else {
		g_game__loop(game);
	}
}

G_COLD
G_INTERNAL G_Game* game_create(void)
{
	if (SDL_Init(SDL_VIDEO | SDL_AUDIO | SDL_TIMER) < 0) {
		SDL_LogCritical(
			SDL_LOG_CATEGORY_SYSTEM, 
			"Unable to initialise SDL backend: %s\n", 
			SDL_GetError()
		);
		g_error_set(ESDL2);
		return;
	}

	const unsigned FIELD_WIDTH = 160;
	const unsigned FIELD_HEIGHT = 120;

	const char* window_title = G_UNAME" ["G_COMPILER" - x86/64]("\
								G_BUILD_MODE")";

	Game* game = g_xmalloc(sizeof(Game));

	game->window = SDL_CreateWindow(
						window_title, 
						SDL_WINDOWPOS_UNDEFINED, 
						SDL_WINDOWPOS_UNDEFINED,
						FIELD_WIDTH, 
						FIELD_HEIGHT, 
						SDL_WINDOW_RESIZABLE
					);

	
	if (game->window == NULL) {
		SDL_LogCritical(
			SDL_LOG_CATEGORY_VIDEO, 
			"Unable to create window: %s\n", 
			SDL_GetError()
		);
		g_game_exit(EXIT_FAILURE);
	}

	game->renderer = SDL_CreateRenderer(
							game->window, 
							G_DEFAULT_RENDERING_DRIVER, 
							G_SDL_NO_FLAGS
						);

	if (game->window == NULL) {
		SDL_LogCritical(
			SDL_LOG_CATEGORY_RENDER, 
			"Unable to create renderer: %s\n", 
			SDL_GetError()
		);
		g_game_exit(EXIT_FAILURE);
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, G_SDL_NEAREST_PIXEL_SAMPLING_FLAG);
	if (SDL_RenderSetLogicalSize(game->renderer, FIELD_WIDTH, FIELD_HEIGHT) < 0) {
		SDL_LogCritical(
			SDL_LOG_CATEGORY_RENDER, 
			"Unable to set renderer logical size: %s\n", 
			SDL_GetError()
		);
		g_game_exit(EXIT_FAILURE);
		
	}

	game->view_id = G_VIEW_MENU;
	game->want_to_run = true;
	
	const int MAP_WIDTH = 64; 
	const int MAP_HEIGHT = 16;
	const unsigned MAP_RENDER_TILE_WIDTH = 16;
	const unsigned MAP_RENDER_TILE_HEIGHT = 16;
	game->map = g_map_create(
					MAP_WIDTH, 
					MAP_HEIGHT, 
					MAP_TILE_WIDTH,
					MAP_TILE_HEIGHT
				);
	gama->camera = g_camera_create();
		
	/*
	game->players = game_players_create(10);
	game->entity_manager = game_entity_manager_create();
	*/
}

void update()
{
	camera->tracking_x = player->pos_x;
	camera->tracking_y = player->pos_y;
}


G_INTERNAL G_GamePlayers* game_players_create(int num_players)
{
	G_GamePlayers* players = xmalloc(sizeof(G_GamePlayers));
	players->players = xmalloc(sizeof(G_GamePlayer) * num_players);

	G_GamePlayer* player_iter = players->players;

	while (player_iter != players->players + num_players) {
		*player_iter++ = create_player();
	}

	players->num = num_players;

	return players;
}

G_GamePlayer* game_player_create(void)
{
	G_GamePlayer* player = xmalloc(sizeof(G_GamePlayer));	
	// ...
}

void game_players_destroy(G_GamePlayers* players)
{
	free(players->players);
	free(players);
}

