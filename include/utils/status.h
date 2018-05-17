#ifndef __utils_status_h__
#define __utils_status_h__

#define GAME_STATUS_SUCCESS_MAP(X_ENTRY) \
	X_ENTRY(DEFAULT, "default status intialisation value") \
	X_ENTRY(SUCCESS, "generic game success") \
	X_ENTRY(EXIT, "successful game exit")

#define GAME_STATUS_FAILURE_MAP(X_ENTRY) \
	X_ENTRY(FAILURE, "generic game failure") \
	X_ENTRY(FNOMEM, "not enough memory") \
	X_ENTRY(FARGINVAL, "invalid arguments") \
	X_ENTRY(FSDL2, "sdl2 specific failure")

#define GAME_STATUS_EXPAND_AS_CASE(status, _) \
	case status:

typedef enum {
	#define GAME_STATUS_SUCCESS_AS_ENUM(status, _) \
		status = 0,
	#define GAME_STATUS_FAILURE_AS_ENUM(status, _) \
		status,

	GAME_STATUS_SUCCESS_MAP(GAME_STATUS_SUCCESS_AS_ENUM)
	GAME_STATUS_FAILURE_MAP(GAME_STATUS_FAILURE_AS_ENUM)

	#undef GAME_STATUS_FAILURE_AS_ENUM
	#undef GAME_STATUS_SUCCESS_AS_ENUM
} GAME_STATUS;

const char* game_status_str(GAME_STATUS status);
const char* game_status_name(GAME_STATUS status);

#endif
