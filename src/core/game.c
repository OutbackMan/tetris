#include "core/game.h"

#include <SDL2/SDL.h>

#include <stdbool.h>

#define ARGTABLE3_IMPLEMENTATION
#include "lib/utils/argtable3.h"
#define XMEM_IMPLEMENTATION
#include "lib/utils/xmem.h"

#include "common.h"
#include "core/loop.h"
#include "core/events.h"
#include "core/update.h"
#include "core/render.h"
#include "core/quit.h"
#include "utils/error.h"

#ifdef BUILD_MODE_DEBUG
#define SDL_ASSERT_LEVEL 2
SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
#elif defined(BUILD_MODE_RELEASE)
#define SDL_ASSERT_LEVEL 1
SDL_LogSetAllPriority(SDL_LOG_PRIORITY_CRITICAL);
SDL_assert/_release();
#endif

GAME_COLD 
void g_game_execute(void)
{
	Game* game = game_create();
	if (game == NULL) {
		SDL_LOG("%s", error_get_msg_str());		
	}

	g_loop__execute(&game);
}

GAME_COLD
GAME_INTERNAL Game* game_create(void)
{
	// parse_args()

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		SDL_LogCritical(
			SDL_LOG_CATEGORY_SYSTEM, 
			"Unable to initialise game SDL backend: %s\n", 
			SDL_GetError()
		);
		return;
	}

	const char* window_title = GAME_UNAME" ["GAME_COMPILER" - x86/64]("\
								GAME_BUILD_MODE")";

	Game* game = xmalloc(sizeof(Game));

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

GAME_INTERNAL G_Player* game_player_create(int num_players)
{
	G_Player* players = xmalloc(sizeof(G_GamePlayer) * num_players);
	for (int i = 0; i < num_players; ++i) {
		// ...
		*players++ = create_player();
	}	
	return players;
}

GAME_INTERNAL G_Map* game_map_create(int width, int height)
{
	G_Map* map = xmalloc(sizeof(G_Map));
	for (int i = 0; i < width * height; i++) {
		map->matrix[i] = SKY;		
	}		
	map->width = width;
	map->height = height;
}
