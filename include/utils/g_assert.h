#ifndef __assert_h__
#define __assert_h__

#include "g_common.h"
#include "utils/g_log.h"

#define GAME_ASSERT(cond, msg, ...) \
	if (!(cond)) { GAME_LOG_FATAL(msg, __VA_ARGS__); GAME_BREAKPOINT(); }

#define GAME_IMPLIES(cond1, cond2) \
	(!(cond1) || (cond2))

#endif
