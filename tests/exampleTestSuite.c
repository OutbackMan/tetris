#include "g_test-helpers.h"

static GAME_TEST_STATUS example_test_a(void)
{
	return GAME_TEST_ASSERT(10 != 10);
}

static GAME_TEST_STATUS example_test_b(void)
{
	return GAME_TEST_ASSERT(10 == 10);
}

GAME_TEST_STATUS tests_exampleTestSuite(int argc, char* argv[argc + 1])
{
	if (game_tests_strcmp(argv[1], "example_test_a")) {
		return example_test_a();
	} else if (game_tests_strcmp(argv[1], "example_test_b")) {
		return example_test_b();
	} else {
		return SUCCESS;
	}
}

