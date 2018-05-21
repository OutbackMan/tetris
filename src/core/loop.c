GAME_COLD 
GAME_INTERNAL GAME_STATUS g_loop__execute(G_Game* game)
{
	obj object_under_control;
	obj camera_tracking_object = object_under_control->px - screen_width / 2;
	bool energising = false;
	float energy_level = 0.0f;
	float camera_x = 0.0f; // actual coordinates lag behind target
	float camera_target_x = 0.0f;
	bool player_has_control = false;
	int player_turn_time;
	
	// human --> SDLK_Z 	
	// player --> ai_controlling & ai_want_jump 
	bool ai_want_jump;

	enum GAME_STATE {
		GS_STATE_1,
		GS_STATE_2
	} current_state, next_state;

	const float DESIRED_FPS = 60.0f;
	const float DESIRED_FRAME_TIME_MS = 1000.0f / DESIRED_FPS;
	const unsigned MAX_UPDATE_STEPS = 6;
	const float MAX_DELTA_TIME = 1.0f;

	while (game->want_to_run) {
		for (u32 prev_ticks = SDL_GetTicks(); !game_is_running; ) {
			u32 cur_ticks = SDL_GetTicks() - prev_ticks;
			prev_ticks = cur_ticks;
			float total_delta_time = cur_ticks / DESIRED_FRAME_TIME_MS;

			if (computer_is_controlling) {
				STRATEGY_TYPE strategy = rand() % NUM_STRATEGIES;		
				if (strategy == DEFENSIVE) {
					
				}
			}

			GAME_STATUS handle_events_status = game_handle_events(
													window, 
													renderer
												);
			if (handle_events_status != SUCCESS) {
				GAME_LOG_FATAL("unable to handle events %s", game_status_str(handle_events_status));		
				return FAILURE;
			}

			unsigned update_counter = 0;
			while (total_delta_time > 0.0f && update_counter < MAX_UPDATE_STEPS) {
				delta_time = G_MATH_FLOAT_MIN(total_delta_time, MAX_DELTA_TIME);
				total_delta_time -= delta_time;
				g_update__execute(game, delta_time);

				++update_counter;
			}

			g_render__execute(game);

		}
	}

	g_exit__execute(game);

	return SUCCESS;
}

