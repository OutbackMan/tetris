#ifdef _MSC_VER
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "utils/log.h"
#include "utils/assert.h"
#include "utils/status.h"
#include "utils/args.h"

int main(int argc, char** argv)
{
	// encapsulate in GAME_INTERNAL game_args_parse()
	// perhaps utilise static struct with extern technique in own file
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

	GAME_STATUS game_run_status = g_game_run();

	GAME_LOG_INFO(
		"Game exited with status: %s", 
		game_str_status(game_run_status)
	);

	return game_run_status;	
}
