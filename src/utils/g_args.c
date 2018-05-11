#include "utils/g_args.h"

#include <string.h>
#include <ctype.h>
#include <stdio.h>

#include "g_common.h"
#include "utils/g_assert.h"
#include "utils/g_log.h"

GAME_INTERNAL const char* game_args__get_arg_type_string(GAME_ARGS_TYPE arg_type);

#if defined(_WIN32)
GAME_INTERNAL const char ARG_START = '\\';
#else
GAME_INTERNAL const char ARG_START = '-';
#endif

GAME_INTERNAL const char* game_args__get_arg_type_string(GAME_ARGS_TYPE arg_type)
{
	if (arg_type == ARG_INT) {
		return "<int>"; 	
	} else if (arg_type == ARG_FILE) {
		return "<file>";
	} else {
		return "";
	}
}

void game_args_print_syntax(GAME_ArgsInstance* arg_table, const size_t arg_table_length)
{
	GAME_ASSERT(GAME_IMPLIES(arg_table_length > 0, arg_table != NULL), "%s", "msg");

	char arg_syntax_buf[512] = "Usage: "GAME_BINARY_STRING" ";

	GAME_ArgsInstance arg_instance;
	for (size_t arg_index = 0; arg_index < arg_table_length; ++arg_index) {
		arg_instance = arg_table[arg_index];

		char arg_option_char_buf[32];	

		snprintf(arg_option_char_buf, sizeof(arg_option_char_buf), "[%c%c%s] ", ARG_START, arg_instance.option_char, game_args__get_arg_type_string(arg_instance.type));

		strcat(arg_syntax_buf, arg_option_char_buf);
	}	
 
	puts(arg_syntax_buf);
}


void game_args_print_glossary(GAME_ArgsInstance* arg_table, const size_t arg_table_length)
{
	GAME_ASSERT(GAME_IMPLIES(arg_table_length > 0, arg_table != NULL), "%s", "msg");

	GAME_ArgsInstance arg_instance;
	for (size_t arg_index = 0; arg_index < arg_table_length; ++arg_index) {
		arg_instance = arg_table[arg_index];

		fprintf(
			stderr, 
			"%c%c%-25s %s.\n", 
			ARG_START,
			arg_instance.option_char,
			game_args__get_arg_type_string(arg_instance.type),
			arg_instance.help_message
		);
	}
}

void game_args_parse(GAME_ArgsInstance* arg_table, const size_t arg_table_length, int argc, char** argv)
{
	GAME_ASSERT(GAME_IMPLIES(arg_table_length > 0, arg_table != NULL), "%s", "msg");

	if (argc < 1) {
		GAME_LOG_INFO("%s", "No arguments provided. Using defaults");
		return;
	}

	for (int arg_pos = 1; arg_pos < argc && argv[arg_pos][0] == ARG_START; ++arg_pos) {
		char* arg_char = argv[arg_pos] + 1;
		while (*arg_char != '\0') {
			GAME_ArgsInstance* arg_instance = NULL;
			bool is_valid_arg = false;
			for (size_t arg_index = 0; arg_index < arg_table_length; ++arg_index) {
				arg_instance = arg_table + arg_index;

				if (*arg_char == arg_instance->option_char) {
					is_valid_arg = true;
					switch(arg_instance->type) {
					case ARG_INT:
						++arg_char;
						arg_instance->i_value = 0;
						while (isdigit(*arg_char)) {
							arg_instance->i_value *= 10;
							arg_instance->i_value += *arg_char - '0';
							++arg_char;
						}	
						break;
					case ARG_BOOL:
						arg_instance->b_value = !arg_instance->b_value;
						++arg_char;	
						break;
					case ARG_FILE:
					{
						const char* str_arg_start = ++arg_char;

						while (isalnum(*arg_char) || *arg_char == '_') {
							++arg_char;
						}	

						strncpy(arg_instance->f_value, str_arg_start, (size_t)(str_arg_start - arg_char));
					} break;
					}
				}
			}	
			if (!is_valid_arg) {
				fprintf(stderr, "Illegal option %c\n", *arg_char);
				fprintf(stderr, "Try '%s %cH' for more information.\n", GAME_BINARY_STRING, ARG_START);
				return;
			}
		}
	}
}
