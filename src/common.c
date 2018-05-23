#include "common.h"

#include <SDL2/SDL.h>
#include <stdlib.h>

void g_exit(int exit_status)
{
	SDL_Quit();	
	exit(exit_status);
}
