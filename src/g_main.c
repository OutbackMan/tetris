#include <SDL2/SDL.h>

#include <stdio.h>
#include <stdlib.h>

#include "g_common.h"
#include "utils/g_log.h"
#include "utils/g_assert.h"

int main(int argc, char* argv[argc + 1])
{
	game_log_init((GAME_LOG_MODE)DEBUG, NULL);

	GAME_BREAKPOINT();

	return EXIT_SUCCESS;	
}
