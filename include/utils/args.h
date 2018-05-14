#ifndef __utils_args_h__
#define __utils_args_h__

#include <stdbool.h>
#include <stddef.h>

typedef enum {
	ARG_INT,
	ARG_BOOL,
	ARG_FILE
} GAME_ARGS_TYPE;

typedef struct {
	GAME_ARGS_TYPE type;
	char option_char;
	const char* help_message;
	union {
		int i_value;
		bool b_value;
		char f_value[64];
	};
} GAME_ArgsInstance;

void game_args_print_syntax(GAME_ArgsInstance* arg_table, const size_t arg_table_length);
void game_args_print_glossary(GAME_ArgsInstance* arg_table, const size_t arg_table_length);
void game_args_parse(GAME_ArgsInstance* arg_table, const size_t arg_table_length, int argc, char** argv);

#endif
