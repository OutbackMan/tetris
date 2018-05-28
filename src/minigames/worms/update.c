
GAME_HOT
GAME_INTERNAL void game_update(G_Game* game, float delta_time)
{
	system_physics(game, delta_time);
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
