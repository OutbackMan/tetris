GAME_INTERNAL void g_render__execute(G_Game* game)
{
	for (int map_x = 0; map_x < map_width; ++map_x) {
		for (int map_y = 0; map_y < map_height; ++map_y) {
			switch(map[(map_y + (int)camera_y) * map_width + (map_x + (int)camera_x)]) {
			case LAND:
				SDL_Colour colour = GREEN;
				SDL_SetRenderDrawColour(renderer, colour->r, ...);	
			case SKY:
				SDL_Colour colour = GREEN;
				SDL_SetRenderDrawColour(renderer, colour->r, ...);	
			}
			SDL_Rect render_block = {
				// ...	
			}
			SDL_FillRectDraw(renderer, render_block);
		}
	}

	for (size_t entity_index = 0; entity_index < MAX_ENTITIES; ++entity_index) {
		if (entity_manager->mask[entity_index] == COMPONENT_RENDERABLE) {
			draw_system();	
		}	
		obj_draw(camera_x, camera_y);
		if (obj == object_under_control) {
			draw_block(x, y, COLOUR);		
		}
	}

	SDL_RenderPresent(renderer);
}
