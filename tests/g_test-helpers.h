#ifndef __tests_test_helpers_h__
#define __tests_test_helpers_h__

typedef enum {
	SUCCESS = 0,
	FAILURE
} GAME_TEST_STATUS;

static int game_tests_strcmp(const char* restrict s1, const char* restrict s2)
{
	while (*s1 && *s1 == *s2) {
		++s1;
		++s2;
	}

	return *s1 - *s2;
}

#endif
