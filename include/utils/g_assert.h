#ifndef __assert_h__
#define __assert_h__

#define GAME_ASSERT(cond, msg) \
	if ((!cond)) { GAME_LOG_FATAL(msg); GAME_BREAKPOINT(); }

#define GAME_IMPLIES(cond1, cond2) \
	(!(cond1) || (cond2))

#endif
