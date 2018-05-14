#include "test-helpers.h"

#include <stdio.h>

int game_tests_strcmp(const char* s1, const char* s2)
{
	while (*s1 && *s1 == *s2) {
		++s1;
		++s2;
	}

	return *s1 - *s2;
}

int game_test_report_failure(const char* file_name, const int line_number, const char* expr)
{
	static const char* ANSI_COLOUR_RED = "\x1b[35m";
	static const char* ANSI_COLOUR_CLEAR = "\x1b[0m";

	return fprintf(stdout, "%s%s:%-4d Did not satisfy %s%s\n", ANSI_COLOUR_RED, file_name, line_number, expr, ANSI_COLOUR_CLEAR);
}
