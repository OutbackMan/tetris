#include <SDL2/SDL.h>

#include <stdio.h>
#include <stdlib.h>

#include "g_common.h"
#include "utils/g_log.h"
#include "utils/g_assert.h"
#include "utils/g_status.h"

GAME_STATUS example(void)
{
	GAME_LOG_INFO("hi there %s", "user");

	return SUCCESS;
}

int main(const int argc, const char* argv[argc + 1])
{
	game_log_init((GAME_LOG_MODE)DEBUG, NULL);

	GAME_STATUS example_status = example();
	GAME_LOG_INFO("example status: %s:%s", game_status_name(example_status), game_status_str(example_status));

	return EXIT_SUCCESS;	
}
