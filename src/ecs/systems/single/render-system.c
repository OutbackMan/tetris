
void g_render_system_execute()
{
	SDL_Rect texture_clip;
	SDL_Rect render_clip;
	RenderComponent render_component;

	for	(int i = 0; i < entity_count; ++i) {
		// perhaps also a bare render, i.e. no rotation
		if (entity_manager->mask[i] == COMPONENT_RENDER) {
			render_component = entity_manager->render_component[i];

			texture_clip = {
				.x = 0, // change to allow for sprite sheets
				.y = 0,
				.w = render_component.w,
				.h = render_component.h
			};
			render_clip = {
				.x = render_component.x,
				.y = render_component.y,
				.w = ,
				.h = 
			};
			SDL_RenderCopyEx(renderer, );
		}
	}
}
