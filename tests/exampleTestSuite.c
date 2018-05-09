#include "g_test-helpers.h"

GAME_TEST_STATUS exampleTestSuite(int argc, char* argv[argc + 1])
{
	if (game_tests_strcmp(argv[1], "example_test_a")) {
		return example_test_a();
	} else if (game_tests_strcmp(argv[1], "example_test_b")) {
		return example_test_b();
	} else {
		return SUCCESS;
	}

	return 0;
}

GAME_TEST_STATUS example_test_a(void)
{
	return 10 == 10;
}

GAME_TEST_STATUS example_test_b(void)
{
	return 20 == 20;
}
