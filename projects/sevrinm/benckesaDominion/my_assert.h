#include <stdio.h>

void _assert(const char* expression, const char* file, int line)
{
	printf("Assertion '%s' failed, file '%s' line'%d'.\n", expression, file, line);
}

int _assertTrue(const char* message)
{
	printf("TEST FAILED: %s\n", message);
	return 0;
}
 
#define my_assert(EXPRESSION) ((EXPRESSION) ? (void)0 : _assert(#EXPRESSION, __FILE__, __LINE__))
#define assertTrue(EXPRESSION, MESSAGE) ((EXPRESSION) ? (int)1 : _assertTrue(#MESSAGE))