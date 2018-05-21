#include "core/game.h"

#include <SDL2/SDL.h>

#include <stdbool.h>

#include "lib/argtable3/argtable.h"

#include "common.h"
#include "core/loop.h"
#include "core/events.h"
#include "core/update.h"
#include "core/render.h"
#include "core/quit.h"
#include "utils/status.h"

GAME_COLD GAME_CHECK
GAME_STATUS g_game_execute(void)
{
	G_Game game;
	GAME_STATUS init_status = game_init(&game);

	if (init_status != SUCCESS) {
		GAME_LOG_FATAL(
			"Unable to initialise game. Status %s\n", 
			game_status_str(init_status);
		);
		return init_status;
	}

	return g_loop__execute(&game);
}

GAME_COLD GAME_CHECK
GAME_INTERNAL GAME_STATUS game_init(G_Game* game, args)
{
	// use sdl variant
	GAME_ASSERT(game != NULL, "%s", "msg");

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		// use sdl variant
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
						args->window_width, 
						args->window_height, 
						SDL_WINDOW_RESIZABLE
					);
	
	if (game->window == NULL) {
		GAME_LOG_FATAL("Unable to create game window: %s\n", SDL_GetError());	
		return FSDL2;
	}

	const int DEFAULT_RENDERING_DRIVER = -1;
	game->renderer = SDL_CreateRenderer(
							game->window, 
							DEFAULT_RENDERING_DRIVER, 
							GAME_SDL_NO_FLAGS
						);

	if (game->renderer == NULL) {
		GAME_LOG_FATAL("Unable to create game renderer: %s\n", SDL_GetError());	
		return FSDL2;
	}

		
	G_Camera camera_placeholder;
	game_camera_create(&camera_placeholder);
	game->camera = &camera_placeholder;		

	G_GamePlayers players;
	GAME_STATUS players_create_status = game_players_create(&players, 10);
	if (players_create_status != SUCCESS) {
		GAME_LOG_FATAL("%s code %s", game_str_status(camera_create_status);
		return FAILURE;
	} else {
		game->players = &players;		
	}

	G_EntityManager entity_manager;
	GAME_STATUS entity_manager_create_status = game_entity_manager_create(game->entity_manager);
	if (entity_manager_create_status != SUCCESS) {
		GAME_LOG_FATAL("%s code %s", game_str_status(camera_create_status);
		return FAILURE;
	} else {
		game->entity_manager = &entity_manager;		
	}

	G_GameMap map;
	GAME_STATUS map_create_status = game_map_create(&map, 500, 500);
	if (game_map_status != SUCCESS) {
		GAME_LOG_FATAL("%s code %s", game_str_status(camera_create_status);
		return FAILURE;
	} else {
		game->map = &map;		
	}

	game->want_to_run = true;

	return SUCCESS;
}

GAME_INTERNAL void game_camera_create(G_GameCamera* camera)
{
	camera->x = 0;
	camera->y = 0;
	camera->target_x = 0;
	camera->target_y = 0;
	camera->tracking_entity_index = 0;
}

GAME_INTERNAL void game_player_create(G_GamePlayer* game_players, int num_players)
{
	game_players->players = malloc(sizeof(G_GamePlayer) * num_players);
	if (game_players->players == NULL) {
		return FNONMEM;		
	} else {
		for (int i = 0; i < num_players; ++i) {
			game_players->player[i] = create_player();
		}	
	}
}

GAME_INTERNAL void game_map_create(G_GameMap* map, int width, int height)
{
	map->matrix = malloc(sizeof(G_MAP_TYPE) * width * height);
	if (map->matrix == NULL) {
		return FNOMEM;		
	} else {
		for (int i = 0; i < width * height; i++) {
			map->matrix[i] = SKY;		
		}		
		map->width = width;
		map->height = height;

		return SUCCESS;
	}
}
