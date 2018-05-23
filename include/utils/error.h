#ifndef __utils_error_h__
#define __utils_error_h__

#define G_ERROR_MAP(X_ENTRY) \
	X_ENTRY(EARGINVAL, "invalid arguments") \
	X_ENTRY(ESDL2, "sdl2 specific failure")

typedef enum {
	#define ERROR_MAP_EXPAND_AS_ENUM(type, _) \
		type,

	G_ERROR_MAP(ERROR_MAP_EXPAND_AS_ENUM)

	#undef ERROR_MAP_EXPAND_AS_ENUM	
} G_ERROR_TYPE;

void g_set_error(ERROR_TYPE type);

const char* g_get_error(void);

#endif
