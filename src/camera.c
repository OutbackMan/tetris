#include "camera.h"

G_Camera* g_camera_create()
{
	G_Camera* camera = xmalloc(sizeof(G_Camera));

	camera->x = 0.0f;
	camera->y = 0.0f;

	return camera;
}
