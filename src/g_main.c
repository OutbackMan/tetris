#include <SDL2/SDL.h>

#include <stdio.h>
#include <stdlib.h>

#include "g_common.h"
#include "utils/g_log.h"

int main(int argc, char* argv[argc + 1])
{
	game_log_init((GAME_LOG_MODE)DEBUG, NULL);

	game_log__log(INFO, "test-file.c", "test_function", 10, "hi %s", "ryan");

	return EXIT_SUCCESS;	
}
