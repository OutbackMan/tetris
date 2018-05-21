#include "core/game.h"

#include <SDL2/SDL.h>

#include <stdbool.h>

#include "common.h"
#include "utils/log.h"
#include "utils/status.h"

GAME_COLD GAME_CHECK
GAME_STATUS g_game_execute(void)
{
	G_Game game = {0};

	GAME_STATUS init_status = game_init(&game);

	switch (init_status) {
	GAME_STATUS_FAILURE_MAP(GAME_STATUS_EXPAND_AS_CASE)
		GAME_LOG_FATAL(
			"Unable to initialise game. Status %s\n", 
			game_status_str(init_status);
		);

		return init_status;
	default:
		break;
	}

	return game_loop();
}

GAME_COLD GAME_CHECK
GAME_INTERNAL GAME_STATUS game_init(G_Game* game, args)
{
	GAME_ASSERT(game != NULL, "%s", "msg");

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		GAME_LOG_FATAL(
			"Unable to initialise game SDL backend: %s\n", 
			SDL_GetError()
		);	

		return FSDL2;
	}

	const char* window_title = GAME_UNAME" ["GAME_COMPILER" - x86/64]("\
								GAME_BUILD_MODE")";

	game->window = SDL_CreateWindow(
						window_title, 
						SDL_WINDOWPOS_UNDEFINED, 
						SDL_WINDOWPOS_UNDEFINED,
						args->window_width, 
						args->window_height, 
						SDL_WINDOW_RESIZABLE
					);
	
	if (game->window == NULL) {
		GAME_LOG_FATAL("Unable to create game window: %s\n", SDL_GetError());	
		return FSDL2;
	}

	const int DEFAULT_RENDERING_DRIVER = -1;
	renderer = SDL_CreateRenderer(
							game_window, 
							DEFAULT_RENDERING_DRIVER, 
							GAME_SDL_NO_FLAGS
						);

	if (renderer == NULL) {
		GAME_LOG_FATAL("Unable to create game renderer: %s\n", SDL_GetError());	
		return FSDL2;
	}

	// other default values

	return SUCCESS;
}


GAME_COLD 
GAME_INTERNAL GAME_STATUS game_loop(void)
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

	for (bool game_is_running = true; !game_is_running; ) {
		for (u32 prev_ticks = SDL_GetTicks(); !game_is_running; ) {
			u32 cur_ticks = SDL_GetTicks() - prev_ticks;
			prev_ticks = cur_ticks;
			float total_delta_time = cur_ticks / DESIRED_FRAME_TIME_MS;

			// FSM control supervisor
			switch (current_state) {
			case GS_STATE_1:		
				some_action();
				next_state = GS_STATE_2;
			}

			if (computer_is_controlling) {
				STRATEGY_TYPE strategy = rand() % NUM_STRATEGIES;		
				if (strategy == DEFENSIVE) {
					
				}
			}

			GAME_STATUS handle_events_status = game_handle_events(
													window, 
													renderer
												);

			switch (handle_events_status) {
			case EXIT:
				game_is_running = false;
			GAME_STATUS_FAILURE_MAP(GAME_STATUS_EXPAND_AS_CASE)
				GAME_LOG_FATAL(
					"Unable to handle game events. Status %s\n", 
					game_status_str(handle_events_status)
				);

				game_exit();

				return handle_events_status;
			GAME_NO_DEFAULT_CASE
			}

			unsigned update_counter = 0;
			while (total_delta_time > 0.0f && update_counter < MAX_UPDATE_STEPS) {
				delta_time = G_MATH_FLOAT_MIN(total_delta_time, MAX_DELTA_TIME);
				total_delta_time -= delta_time;
				game_update(delta_time);

				++update_counter;
			}

			render();

		}
	}

	game_exit();

	return SUCCESS;
}

GAME_HOT
GAME_INTERNAL void game_update(float delta_time)
{
	physics_system(entity_manager);
	for (all_physics_objects) {
		obj->ay += 2.0f; // gravity		

		obj->vx += obj->ax * delta_time;
		obj->vy += obj->ay * delta_time;

		float potential_x = obj->px + obj->vx * delta_time;
		float potential_y = obj->py + obj->vy * delta_time;

		obj->ax = 0.0f;
		obj->ay = 0.0f;
		obj->is_stable = false;

		float collision_angle = atan2f(obj->vx, obj->vy);
		float response_x = 0.0f;
		float response_y = 0.0f;
		bool collision_encountered = false;

		// circle and rectangle collisions take similar times to perform, so pick the one that makes most sense for context and that allows to minimise function calls
		// iterate through semicircle
		// have arbitrarily chosen small increment to ensure a sufficient amount of pixels are tested 
		for (float r = collision_angle - PI / 2; r < collision_angle + PI / 2; r += PI / 8.0f) {
			float test_pos_x = obj->collision_radius * cosf(r) + potential_x;
			float test_pos_y = obj->collision_radius * sinf(r) + potential_y;

			// clamp test values (always do when reading from memory)
			if (map[(int)test_pos_y * map_width + (int)test_pos_x] != SKY) {
				response_x += potential_x - test_pos_x;	
				response_y += potential_y - test_pos_y;	
				collision_encountered = true;
			}

		}
		
		if (collision_encountered) {
			// response vector as normal to tangent of terrain
			// used for reflection calculation for bounce
			obj->stable = true;	
			float velocity_magnitude = sqrtf(obj->px*obj->px + obj->py*obj->py);
			float response_magnitude = sqrtf(response_x*response_x + response_y*response_y);
			// calculate reflection vector
			// account for friction
		} else {
			obj->px = potential_x;
			obj->py = potential_y;
		}

		if (obj->is_dead) {
			int on_dead_response = dead_response(obj);
			if (on_dead_response == EXPLODE) {
				boom(x, y);		
			}
		}

		if (fire_weapon) {
			
		}
	}
}

GAME_INTERNAL void game_render(SDL_Renderer* renderer)
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


GAME_COLD
GAME_INTERNAL void game_quit(SDL_Window* window, SDL_Renderer* renderer)
{
	if (renderer != NULL) SDL_DestroyRenderer(renderer);
	if (window != NULL) SDL_DestroyWindow(window);
	if (SDL_WasInit(SDL_INIT_EVERYTHING)) SDL_Quit();
}
