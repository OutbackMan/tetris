#include "utils/g_args.h"

#include "g_common.h"
#include "utils/g_assert.h"
#include "utils/g_log.h"

GAME_ArgTable game_args_default_arg_table = {
	.length = 5,
	.arg_help = {
		.type = ARG_BOOL,
		.option_char = 'H',
		.default_value = false,
		.help_message = "Display this help and exit"
	},
	.arg_version = {
		.type = ARG_BOOL,
		.option_char = 'V',
		.default_value = false,
		.help_message = "Display version information and exit"
	},
	.save_file = {
		.type = ARG_FILE,
		.option_char = 'S',
		.default_value = GAME_LNAME".sav",
		.help_message = "Specify location of save file"
	},
	.game_width = {
		.type = ARG_INT,
		.option_char = 'W',
		.default_value = 640,
		.help_message = "Specify width of "GAME_LNAME" screen in pixels"
	},
	.game_height = {
		.type = ARG_INT,
		.option_char = 'H',
		.default_value = 480,
		.help_message = "Specify height of "GAME_LNAME" screen in pixels"
	}
};

#define GAME_ARGS__ARG_TABLE_ITERATE(arg_index, arg) \
	for ( \
			size_t arg_index = 1; \
			GAME__ArgInstance arg = game_args_default_arg_table[arg_index]; \
			arg_index < arg_table.length; \
			++arg_index \
		)


void game_args_print_syntax(FILE* output_stream)
{
	// calloc() takes sizeof(space) to zero, so consider using malloc if speed is a consideration
	GAME_ASSERT(output_stream != NULL, "msg");

	char arg_syntax_buf[512] = "Usage: "GAME_BINARY_STRING" ";

	GAME_ARG_TABLE_ITERATE(_, arg) {
		char arg_option_char_buf[32];	

		snprintf(arg_option_char_buf, sizeof(arg_option_char_buf), "[-%c%s] ", arg.option_char, game_args__get_arg_type_string(arg.type));

		strcat(arg_syntax_buf, arg_option_char_buf);
	}	

	fprintf(output_stream, "%s\n", arg_syntax_buf);
}

static const char* game_args__get_arg_type_string(GAME_ARG_TYPE arg_type)
{
	GAME_ASSERT(arg != NULL, "msg");

	if (arg_type == ARG_INT) {
		return "<int>"; 	
	} else if (arg_type == ARG_FILE) {
		return "<file>";
	} else {
		return "";
	}
}

void game_args_print_glossary(FILE* output_stream)
{
	GAME_ASSERT(output_stream != NULL, "msg");

	GAME_ARG_TABLE_ITERATE(_, arg) {
		fprintf(
			output_stream, 
			"-%c%-25s %s.\n", 
			arg.option_char,
			game_args__get_arg_type_string(arg.type),
			arg.help_message
		);
	}
}

void game_args_parse(const int argc, const char** argv)
{
	if (argc < 1) {
		GAME_LOG_INFO("%s", "No arguments provided. Using defaults");
		return;
	}

#if defined(_WIN32)
	const char ARG_START = '\\';
#else
	const char ARG_START = '-';
#endif

	for (size_t arg_index = 1; arg_index < argc && argv[arg_index][0] == ARG_START; ++arg_index) {
		for (char* arg_char = argv[arg_index] + 1; *arg_char != '\0'; ++arg_char) {
			GAME_ARG_TABLE_ITERATE(_, arg) {
				if (*arg_char == arg.option_char) {
					game_args__parse_arg(&arg, arg_char);	
				} else {
					fprintf(stderr, "Illegal option %c\n", *arg_char);
					fprintf(stderr, "Try '%s %cH' for more information.\n", GAME_BINARY_STRING, ARG_START);
					return;
				}
			}	
		}
	}
}

void game_args__parse_arg(GAME__ArgInstance* arg, char* arg_char)
{
	GAME_ASSERT(arg != NULL, "msg");	

	switch(arg.type) {
	case ARG_INT:
		while (isdigit(*arg_char)) {
			arg->value *= 10;
			arg->value += *arg_char - '0';
			++arg_char;
		}	
		break;
	case ARG_BOOL:
		arg.value = !arg.value;
		++arg_char;	
		break;
	case ARG_FILE:
		const char* str_arg_start = arg_char;

		while (isalnum(*arg_char) || *arg_char == '_') {
			++arg_char;
		}	
		
		char file_name[32];
		strncpy(file_name, str_arg_start, (size_t)(str_arg_start - arg_char));
			
		arg.value = fopen(file_name, "a");
		break;	
	}
}
