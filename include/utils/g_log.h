#ifndef __utils_log_h__
#define __utils_log_h__

#include <stdio.h>
#include <stdarg.h>

typedef enum  {
	INFO, 
	WARN, 
	FATAL,
	NUM
} GAME_LOG_TYPE;

typedef enum {
	DEBUG,
	RELEASE
} GAME_LOG_MODE;

void game_log__log(
	GAME_LOG_TYPE log_level, 
	const char* restrict file_name, 
	const char* restrict function_name, 
	const int line_number, 
	const char* restrict message_fmt, ...
);

void game_log_init(GAME_LOG_MODE log_mode, FILE* log_file);

#define GAME_LOG_INFO(msg, ...) \
	game_log__log((GAME_LOG_TYPE)INFO,  __FILE__, __func__, __LINE__, msg, __VA_ARGS__)
#define GAME_LOG_WARN(msg, ...) \
	game_log__log((GAME_LOG_TYPE)WARN,  __FILE__, __func__, __LINE__, msg, __VA_ARGS__)
#define GAME_LOG_FATAL(msg, ...) \
	game_log__log((GAME_LOG_TYPE)FATAL, __FILE__, __func__, __LINE__, msg, __VA_ARGS__)

#endif
