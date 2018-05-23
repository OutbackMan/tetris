typedef struct {
	int x;
	int y;
	SDL_Texture* texture;
	unsigned width;
	unsigned height;
	unsigned width_scale;
	unsigned height_scale;
	int sheet_mapping[sheet_count];
} SpriteComponent;
