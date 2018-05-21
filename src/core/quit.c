

GAME_COLD
GAME_INTERNAL void game_quit(SDL_Window* window, SDL_Renderer* renderer)
{
	if (renderer != NULL) SDL_DestroyRenderer(renderer);
	if (window != NULL) SDL_DestroyWindow(window);
	if (SDL_WasInit(SDL_INIT_EVERYTHING)) SDL_Quit();
}
