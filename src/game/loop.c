#include "core/loop.h"

#include "common.h"

GAME_COLD 
GAME_INTERNAL void g_loop__execute(
						G_Game* game, 
						float desired_fps, 
						unsigned max_update_steps, 
						float max_delta_time
					)
{
	const float DESIRED_FRAME_TIME_MS = 1000.0f / desired_fps;

	float total_delta_time = G_FLOAT_DEFAULT;
	unsigned update_counter = G_UINT_DEFAULT; 

	while (game->want_to_run) {
		for (u32 prev_frame_time = SDL_GetTicks(); !game->want_to_run; ) {
			u32 cur_frame_time = SDL_GetTicks() - prev_frame_time;
			prev_frame_time= cur_frame_time;
			total_delta_time = cur_ticks / DESIRED_FRAME_TIME_MS;

			// #include "game/event-handlers.h"
			switch (game->view_id) {
				G_EVENT_HANDLERS_MAP(EXPAND_AS_CASE)
			}

			update_counter = 0;
			while (total_delta_time > 0.0f && update_counter < max_update_steps) {
				delta_time = G_MATH_FLOAT_MIN(total_delta_time, max_delta_time);
				total_delta_time -= delta_time;

				switch (game->view_id) {
					G_UPDATE_HANDLERS_MAP(EXPAND_AS_CASE)
				}

				++update_counter;
			}

			switch (game->view_id) {
				G_RENDER_HANDLERS_MAP(EXPAND_AS_CASE)
			}

		}
	}

	g_exit__execute(game);

	return SUCCESS;
}
