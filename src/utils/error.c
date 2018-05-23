#include "utils/error.h"

#include "common.h"

static struct {
	ERROR_TYPE current_error_type;		
} __ERROR;

#define ERROR_MAP_EXPAND_AS_CASE(type, msg) \
	case type: return [ ## type ## ] ## msg; 	
const char* g_get_error(void)
{
	switch (type) {
		G_ERROR_MAP(ERROR_MAP_EXPAND_AS_CASE)		
	default:
		return "unknown error";
	}
}
#undef ERROR_MAP_EXPAND_AS_CASE

void g_set_error(ERROR_TYPE error_type)
{
	__ERROR.current_error_type = error_type;		
}

