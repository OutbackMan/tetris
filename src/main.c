#include <SDL2/SDL.h>

#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "core/game/game.h"

int main(int argc, char** argv)
{
#ifdef G_BUILD_MODE_RELEASE
#define SDL_ASSERT_LEVEL 1
	SDL_LogSetAllPriority(SDL_LOG_PRIORITY_CRITICAL);
#elif defined(G_BUILD_MODE_DEBUG)
#define SDL_ASSERT_LEVEL 2
	SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
#endif

	g_game_execute();

	return EXIT_SUCCESS;	
}
