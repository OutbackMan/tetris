#ifndef __core_game_camera_h__
#define __core_game_camera_h__

typedef struct {
	int x;
	int y;
	int target_x;
	int target_y;
	int tracking_entity_index;
} G_Camera;

G_Camera* g_camera_create();
void g_camera_destroy();

#endif
