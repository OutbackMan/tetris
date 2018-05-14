#include "utils/status.h"

#include <stdbool.h>

#define EXPAND_GAME_STATUS_AS_CASE(status, str) \
	case status: return str; 	
const char* game_status_str(GAME_STATUS status)
{
	switch (status) {
		GAME_STATUS_MAP(EXPAND_GAME_STATUS_AS_CASE)				
	}		
	
	return "unknown status";
}
#undef EXPAND_GAME_STATUS_AS_CASE

#define EXPAND_GAME_STATUS_AS_CASE(status, _) \
	case status: return #status; 	
const char* game_status_name(GAME_STATUS status)
{
	switch (status) {
		GAME_STATUS_MAP(EXPAND_GAME_STATUS_AS_CASE)				
	}		
	
	return "unknown status";
}
#undef EXPAND_GAME_STATUS_AS_CASE
