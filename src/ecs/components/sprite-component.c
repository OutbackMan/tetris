typedef struct {
	SDL_Texture* texture;
	unsigned width;
	unsigned height;
	unsigned width_scale;
	unsigned height_scale;
} SpriteComponent;

// assume sheets are same width and height
SpriteComponent* sprite_component_create(
	const char* filename,
	unsigned width_scale,
	unsigned height_scale,
)
{
	SpriteComponent* sprite_component = xmalloc(sizeof(SpriteComponent));

	SDL_Surface* sprite_surface = SDL_LoadBMP(filename);
	if (sprite_surface == NULL) {
		
	}

	sprite_component->texture = SDL_CreateTextureFromSurface(sprite_surface);
	if (sprite_component->texture == NULL) {
		
	}
	SDL_FreeSurface(sprite_surface);

	if (SDL_QueryTexture(texture, NULL, NULL, sprite_component->width, sprite_component->height) < 0) {
		// ..	
	}

	sprite_component->width_scale = width_scale;
	sprite_component->height_scale = height_scale;

	return sprite_component;
}

void sprite_system_draw()
{
	
}

// concerned with interactions
typedef struct {
	bool can_pass_through_solids;
	bool can_pass_through_dynamics;
	bool is_friendly;
} DynamicComponent;
