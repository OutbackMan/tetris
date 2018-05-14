#ifndef __tests_test_helpers_h__
#define __tests_test_helpers_h__

typedef enum {
	SUCCESS = 0,
	FAILURE
} GAME_TEST_STATUS;

#define GAME_TEST_ASSERT(expr) \
	(!(expr) ? (game_test_report_failure(__FILE__, __LINE__, #expr), FAILURE) : SUCCESS)

int game_test_report_failure(const char* file_name, const int line_number, const char* expr);

int game_tests_strcmp(const char* s1, const char* s2);

#endif
