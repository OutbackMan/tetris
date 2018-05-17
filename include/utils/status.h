#ifndef __utils_status_h__
#define __utils_status_h__

#define GAME_STATUS_MAP(X_ENTRY) \
	X_ENTRY(DEFAULT, "default status intialisation value") \
	X_ENTRY(SUCCESS, "generic game success") \
	X_ENTRY(FAILURE, "generic game failure") \
	X_ENTRY(EXIT, "normal game flow exit") \
	X_ENTRY(FNOMEM, "not enough memory") \
	X_ENTRY(FARGINVAL, "invalid arguments") \
	X_ENTRY(FSDL2, "sdl2 specific failure")

typedef enum {
	#define EXPAND_GAME_STATUS_AS_ENUM(status, _) \
		status,

	GAME_STATUS_MAP(EXPAND_GAME_STATUS_AS_ENUM)

	#undef EXPAND_GAME_STATUS_AS_ENUM
} GAME_STATUS;

const char* game_status_str(GAME_STATUS status);
const char* game_status_name(GAME_STATUS status);

#endif
