#ifndef __utils_args_h__
#define __utils_args_h__

typedef enum {
	ARG_INT,
	ARG_BOOL,
	ARG_FILE
} GAME_ARG_TYPE;

typedef struct {
	GAME_ARG_TYPE arg_type;
	char option_char;
	union {
		int value;
		bool value;
		FILE* value;
	}
	const char* help_message;
} GAME__ArgInstance;

typedef struct {
	size_t length;
	GAME__ArgInstance arg_help;
	GAME__ArgInstance arg_version;
	GAME__ArgInstance arg_save_file;
	GAME__ArgInstance arg_width;
	GAME__ArgInstance arg_height;
} GAME_ArgTable;

extern const GAME_ArgTable game_args_default_arg_table; 

void game_args_print_syntax(FILE* output_stream);
void game_args_print_glossary(FILE* output_stream)
void game_args_handle(const int argc, const char** argv)

#endif
