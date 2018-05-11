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

void game_args_print_syntax(FILE* output_stream);
void game_args_print_glossary(FILE* output_stream)
void game_args_parse(GAME_ArgTable* arg_table, const int argc, const char** argv)

#endif
