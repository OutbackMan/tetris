#include "utils/log.h"

#include <time.h>
#include <stdio.h>
#include <stdarg.h>

#include "common.h"
#include "utils/ansi-colours.h"

GAME_INTERNAL struct {
	bool in_release_mode;	
	const char* type_names[(GAME_LOG_TYPE)NUM];
	const char* type_colours[(GAME_LOG_TYPE)NUM];
	FILE* log_file;
} __log = {
	.in_release_mode = false,	
	.type_names = {"INFO", "WARN", "FATAL"},
	.type_colours = {ANSI_COLOUR_GREEN, ANSI_COLOUR_ORANGE, ANSI_COLOUR_RED},
	.log_file = NULL
};

void game_log_init(GAME_LOG_MODE log_mode, FILE* log_file)
{
	if (log_mode == DEBUG) {
		__log.in_release_mode = false; 	
	} else {
		__log.in_release_mode = true; 	
	}
	
	__log.log_file = log_file;
}

void game_log__log(
	GAME_LOG_TYPE log_type, 
	const char* file_name, 
	const char* function_name, 
	const int line_number, 
	const char* message_fmt, ...
)
{
	if (__log.in_release_mode && log_type != FATAL) {
		return;		
	}

	time_t current_time = time(NULL);	
	struct tm* local_time = localtime(&current_time);

	char time_string_buf[64];

	GAME_LOCAL_PERSIST const char* TIME_FORMAT_STR = "%H:%M:%S";
	size_t time_string_length = strftime(
					      time_string_buf,
					      sizeof(time_string_buf), 
					      TIME_FORMAT_STR, 
					      local_time
					     ); 
	time_string_buf[time_string_length] = '\0';
	
	va_list args;

	if (__log.log_file != NULL) {
		fprintf(
			__log.log_file, 
			"%s %-5s %s:%s:%d ", 
			time_string_buf, 
			__log.type_names[log_type], 
			file_name, 
			function_name, 
			line_number
		);
		va_start(args, message_fmt);
		vfprintf(__log.log_file, message_fmt, args);
		va_end(args);
		fprintf(__log.log_file, "\n");
	} else {
		fprintf(
			stderr, 
			"%-8s %s%-5s%s %s%s:%s:%d%s ", 
			time_string_buf, 
			__log.type_colours[log_type], 
			__log.type_names[log_type], 
			ANSI_COLOUR_CLEAR,
			ANSI_COLOUR_GREY,
			file_name, 
			function_name, 
			line_number,
			ANSI_COLOUR_CLEAR
		);
		va_start(args, message_fmt);
		vfprintf(stderr, message_fmt, args);
		va_end(args);
		fprintf(stderr, "\n");
	}
}
