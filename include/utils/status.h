#ifndef __utils_status_h__
#define __utils_status_h__

#define GAME_STATUS_MAP(X_ENTRY) \
	X_ENTRY(ENTERED, "entered function") \
	X_ENTRY(SUCCESS, "generic game success") \
	X_ENTRY(FAILURE, "generic game failure") \
	X_ENTRY(FNOMEM, "not enough memory") \
	X_ENTRY(FARGINVAL, "invalid arguments") 

typedef enum {
	#define EXPAND_GAME_STATUS_AS_ENUM(status, _) \
		status,

	GAME_STATUS_MAP(EXPAND_GAME_STATUS_AS_ENUM)

	#undef EXPAND_GAME_STATUS_AS_ENUM
} GAME_STATUS;

const char* game_status_str(GAME_STATUS status);
const char* game_status_name(GAME_STATUS status);

#endif
