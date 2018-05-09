#include "g_test-helpers.h"

int example_test_a(void);
int example_test_b(void);

int tests_exampleTestSuite(int argc, char* argv[argc + 1])
{
	if (game_tests_strcmp(argv[1], "example_test_a")) {
		return example_test_a();
	} else if (game_tests_strcmp(argv[1], "example_test_b")) {
		return example_test_b();
	} else {
		return 0;
	}
}

int example_test_a(void)
{
	return 0;
}

int example_test_b(void)
{
	return 0;
}
