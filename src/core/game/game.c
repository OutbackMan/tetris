#include "core/game/game.h"

#include <SDL2/SDL.h>

#include <stdbool.h>
#include <stdlib.h>

#include "lib/argtable3.h"

#include "common.h"
#include "core/game/camera.h"
#include "core/game/map.h"
#include "core/game/players.h"
#include "core/loop.h"
#include "utils/error.h"
#include "utils/xmem.h"

#ifdef G_BUILD_MODE_RELEASE
#define SDL_ASSERT_LEVEL 1
SDL_LogSetAllPriority(SDL_LOG_PRIORITY_CRITICAL);
#elif defined(G_BUILD_MODE_DEBUG)
#define SDL_ASSERT_LEVEL 2
SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
#endif

inline void g_game_exit(int exit_status)
{
	SDL_Quit();
	exit(exit_status);
}

GAME_COLD 
void g_game_execute(void)
{
	Game* game = game_create();
	if (game == NULL) {
		SDL_LogCritical(
			SDL_LOG_CATEGORY_APPLICATION, 
			"Unable to create game instance %s", 
			g_error_get()
		);
		return;
	} else {
		g_loop__execute(game);
	}
}

GAME_COLD
GAME_INTERNAL Game* game_create(void)
{
	// parse_args()
	Game* game = NULL;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		SDL_LogCritical(
			SDL_LOG_CATEGORY_SYSTEM, 
			"Unable to initialise game SDL backend: %s\n", 
			SDL_GetError()
		);
		g_error_set(ESDL2);
		return;
	}

	const char* window_title = GAME_UNAME" ["GAME_COMPILER" - x86/64]("\
								GAME_BUILD_MODE")";

	game = xmalloc(sizeof(Game));

	game->window = SDL_CreateWindow(
						window_title, 
						SDL_WINDOWPOS_UNDEFINED, 
						SDL_WINDOWPOS_UNDEFINED,
						args->window_width, 
						args->window_height, 
						SDL_WINDOW_RESIZABLE
					);
	
	if (game->window == NULL) {
		SDL_LogCritical(
			SDL_LOG_CATEGORY_VIDEO, 
			"Unable to create gmae window: %s\n", 
			SDL_GetError()
		);
		g_game_exit(EXIT_FAILURE);
	}

	const int DEFAULT_RENDERING_DRIVER = -1;
	game->renderer = SDL_CreateRenderer(
							game->window, 
							DEFAULT_RENDERING_DRIVER, 
							GAME_SDL_NO_FLAGS
						);

	if (game->window == NULL) {
		SDL_LogCritical(
			SDL_LOG_CATEGORY_RENDER, 
			"Unable to create game renderer: %s\n", 
			SDL_GetError()
		);
		g_game_exit(EXIT_FAILURE);
	}

		
	game->camera = game_camera_create();
	game->players = game_players_create(10);
	game->entity_manager = game_entity_manager_create();
	game->map = game_map_create(500, 500);
	game->want_to_run = true;
}

GAME_INTERNAL G_Camera* game_camera_create()
{
	G_Camera* camera = xmalloc(sizeof(G_Camera));

	camera->x = 0;
	camera->y = 0;
	camera->target_x = 0;
	camera->target_y = 0;
	camera->tracking_entity_index = 0;

	return camera;
}

GAME_INTERNAL G_GamePlayers* game_players_create(int num_players)
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

