
// component_wireframe would include rotation
// have wireframe_draw_system() RenderCopyEx()
#define RENDER_MASK COMPONENT_SPRITE | COMPONENT_POSITION
void g_object_draw_system_execute()
{
	SDL_Rect texture_clip;
	SDL_Rect render_clip;
	SpriteComponent* sprite_component;
	PositionComponent* position_component;

	for	(int i = 0; i < entity_count; ++i) {
		if (entity_manager->mask[i] == RENDER_MASK) {
			sprite_component = entity_manager->sprite_component[i];
			position_component = entity_manager->position_component[i];

			texture_clip = {
				.x = sprite_component->sheet_index * sprite_component->base_width,
				.y = sprite_component->sheet_index * sprite_component->base_width,
				.w = sprite_component->base_width,
				.h = sprite_component->base_height
			};

			render_clip = {
				.x = position_component->x,
				.y = position_component->y,
				.w = ,
				.h = ,
			};

			SDL_RenderCopy(renderer, );
		}
	}
}
