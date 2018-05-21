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
	switch (event->type) {
	case SDL_QUIT:
		game->want_to_run = false;
		break;
	case SDL_WINDOWEVENT:
		break;
	case SDL_KEYUP:
	case SDL_KEYDOWN:
		events_handle_keyboard(event->key);
		break;
	case SDL_MOUSEBUTTONUP:
	case SDL_MOUSEBUTTONDOWN:
		events_handle_mouse_buttons();
		break;
	case SDL_MOUSEMOTION:
		events_handle_mouse_motion();
		break;
	}
}

GAME_INTERNAL
GAME_STATUS game_handle_window_events(G_GameWindow* game_window, SDL_WindowEvent* event)
{
	switch (window_event->event) {
	case SDL_WINDOWEVENT_RESIZED:
		// ..
		break;
	case SDL_WINDOWEVENT_EXPOSED:
		game_window->is_exposed = true;
		break;

}

GAME_INTERNAL GAME_STATUS events_handle_keyboard(G_Game* game, SDL_KeybordEvent* keyboard_event)
{
	const bool KEY_IS_PRESSED = (keyboard_event->state == SDL_PRESSED);

	// and escape
	if (keyboard_event->keysym.sym == SDLK_q && keyboard_event->keysym.mod == KMOD_CTRL) {
		game->want_to_run = false;
	}

	
	if (keyboard_event->keysym.sym == SDLK_w && !keyboard_event->repeat)
		create_map(game->map, game->map->width, game->map->height);
	}

	case SDLK_X:
	// jump
		physics_system_jump(entity_manager, true);
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
