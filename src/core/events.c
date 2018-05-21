GAME_HOT GAME_CHECK 
GAME_STATUS game_handle_events(G_Game* game)
{
	GAME_STATUS handle_event_status = DEFAULT;

	SDL_Event event = {0};
	while (SDL_PollEvent(&event)) {
		handle_event_status = game_handle_event(event.type);

		if (handle_event_status != SUCCESS) {
			GAME_LOG_FATAL(
				"Unable to handle game event. Status %s\n", 
				game_status_str(handle_event_status)
			);

			return handle_event_status;
		}
	}

	return SUCCESS;
}

GAME_HOT GAME_CHECK 
GAME_INTERNAL GAME_STATUS game_handle_event(SDL_Event* event)
{
	if (event->type == SDL_QUIT) {
		game->want_to_run = false;
		break;
	} else if (event->type == SDL_WINDOWEVENT) {
		GAME_STATUS handle_window_events_status = game_handle_window_events(
														&event->window
													);
		if (handle_window_events_status != SUCCESS) {
			GAME_LOG_FATAL(
				"Unable to handle game event. Status %s\n", 
				game_status_str(handle_event_status)
			);

			return handle_event_status;
		}
	} else if (event->type == SDL_KEYDOWN) {
		game_handle_keyboard_events(game, &event->key);
	} else {
		return SUCCESS;		
	}
}

GAME_INTERNAL
GAME_STATUS game_handle_window_events(SDL_WindowEvent* event)
{
	switch (window_event->event) {
	case SDL_WINDOWEVENT_RESIZED:
		// ..
		break;
	case SDL_WINDOWEVENT_EXPOSED:
		game_render();
		break;

}

bool keyonce(keycode, keystate)
{
	static bool old = false;
	bool res = keystate[keycode] && !old;
	old = keystate[keycode];
	return res;
}
        Uint8 *keystate = SDL_GetKeyState(NULL);

#define KEYONCE(scancode, keystate) \



        #define keyonce(n) \
            [&keystate]() -> bool { \
                static bool old=false; \
                bool res = keystate[n] && !old; \
                old = keystate[n]; \
                return res; }()

        // Put new keys into the device's keyboard buffer.
        static unsigned keyptr = 0;
        if(keyonce(SDLK_UP))


const uint8_t* keystate = SDL_GetKeyboardState(NULL);
GAME_INTERNAL GAME_STATUS game_handle_keyboard_events(G_Game* game, const uint8_t* keystate)
{
	if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_LCTRL] && keystate[SDL_SCANCODE_Q]) {
		game->want_to_run = false	
	} else if (keystate[SDL_SCANCODE_W]) {
		// key_w_sentinel
		static bool right_key_down = false;	
		bool current = keystate[SDL_SCANCODE_RIGHT] && !right_key_down;
		right_key_down = keystate[n];
		if (current) {
			// key once
			create_map(game->map->field, game->map->width, game->map->height);
		}
		// is held if pressed previously but not now

	}
	case SDLK_X:
	// jump
		entity_manager->physics[entity_under_control].is_stable;
				object_under_control->vx = +4.0f;		
				object_under_control->vy = -8.0f;		
				object_under_control->is_stable = false;		
			}	
		}
	case SDLK_Z:
	// jump
		if (object_under_control != NULL) {
			if (object_under_control->is_stable) {
				object_under_control->vx = -4.0f;		
				object_under_control->vy = -8.0f;		
				object_under_control->is_stable = false;		
			}	
		}
	case SDLK_A_IS_HELD:
	object_under_control->shoot_angle -= 1.0f * delta_time;
	case SDLK_SPACE:
	energising = true;
	energy_level = 0.0f;
	case SDLK_SPACE_IS_HELD:
	if (energising) {
		energy_level += 0.75f * delta_time;
		if (energy_level >= 1.0f) {
			energy_level = 1.0f;		
		}
	}
	case SDLK_SPACE_IS_RELEASED:
	fire_weapon = true;
	energising = false;

	}
}

uint32_t* SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)
GAME_INTERNAL GAME_STATUS game_handle_mouse_button_events(SDL_MouseButtonEvent* mouse_motion_event)
{
	if (event->button == SDL_BUTTON_MIDDLE) {
		// create PHYSICS | RENDERABLE component
		add_drawable_physics_object(mouse_x + camera_x, mouse_y + camera_y);		
	}

	if (event->button == SDL_BUTTON_LEFT) {
		add_20_debris_objects(mouse_x + camera_x, mouse_y + camera_y);
		// append to list of game objects
	}
}

GAME_INTERNAL GAME_STATUS game_handle_mouse_motion_events(SDL_MouseMotionEvent* mouse_motion_event)
{
	float map_scroll_speed = 400.0f;
	if (event->x < 5) camera_pos_x -= map_scroll_speed * delta_time;
	if (event->x > window_width - 5) camera_pos_x += map_scroll_speed * delta_time;
	if (event->y < 5) camera_pos_y += map_scroll_speed * delta_time;
	if (event->y > window_height - 5) camera_pos_y += map_scroll_speed * delta_time;
	// must also clamp to map boundaries
}
