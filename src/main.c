#include <SDL2/SDL.h>

#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "utils/log.h"
#include "utils/assert.h"
#include "utils/status.h"
#include "utils/args.h"

int main(int argc, char** argv)
{
	GAME_STATUS game_run_status = g_game_execute();

	// SDL_Log
	GAME_LOG_INFO(
		"Game exited with status: %s", 
		game_str_status(game_run_status)
	);

	return game_run_status;	
}
