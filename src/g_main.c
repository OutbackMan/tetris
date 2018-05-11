#include <SDL2/SDL.h>

#include <stdio.h>
#include <stdlib.h>

#include "g_common.h"
#include "utils/g_log.h"
#include "utils/g_assert.h"
#include "utils/g_status.h"
#include "utils/g_args.h"

int main(int argc, char** argv)
{
	enum { HELP_ARG, VERSION_ARG, SAVE_FILE_ARG, WIDTH_ARG, HEIGHT_ARG, ARG__NUM };

	GAME_ArgsInstance arg_table[ARG__NUM] = {
		[HELP_ARG] = {
			.type = ARG_BOOL,
			.option_char = 'H',
			.help_message = "Display this help and exit",
			.b_value = false,
		},
		[VERSION_ARG] = {
			.type = ARG_BOOL,
			.option_char = 'V',
			.help_message = "Display version information and exit",
			.b_value = false,
		},
		[SAVE_FILE_ARG] = {
			.type = ARG_FILE,
			.option_char = 'S',
			.help_message = "Specify location of save file",
			.f_value = GAME_LNAME".sav",
		},
		[WIDTH_ARG] = {
			.type = ARG_INT,
			.option_char = 'W',
			.help_message = "Specify width of "GAME_LNAME" screen in pixels",
			.i_value = 640,
		},
		[HEIGHT_ARG] = {
			.type = ARG_INT,
			.option_char = 'H',
			.help_message = "Specify height of "GAME_LNAME" screen in pixels",
			.i_value = 480,
		}
	};

	game_args_parse(arg_table, ARG__NUM, argc, argv);
	
	if (arg_table[HELP_ARG].b_value == true) {
		game_args_print_syntax(arg_table, ARG__NUM);
		puts(GAME_DESCRIPTION);
		game_args_print_glossary(arg_table, ARG__NUM);
	}

	game_start(arg_table[WIDTH_ARG].i_value, arg_table[HEIGHT_ARG].i_value);

	return EXIT_SUCCESS;	
}
