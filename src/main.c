#include <SDL2/SDL.h>

#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "game.h"

int main(int argc, char** argv)
{
#ifdef G_BUILD_MODE_RELEASE
#define SDL_ASSERT_LEVEL 1
	SDL_LogSetAllPriority(SDL_LOG_PRIORITY_CRITICAL);
#elif defined(G_BUILD_MODE_DEBUG)
#define SDL_ASSERT_LEVEL 2
	SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
#endif

	const float DESIRED_FPS = 60.0f;
	const unsigned MAX_UPDATE_STEPS = 6;

	g_game_execute(DESIRED_FPS, MAX_UPDATE_STEPS);

	return EXIT_SUCCESS;	
}
