#include <stdio.h>

void _assert(const char* expression, const char* file, int line)
{
	printf("Assertion '%s' failed, file '%s' line'%d'.\n", expression, file, line);
}
 
#define my_assert(EXPRESSION) ((EXPRESSION) ? (void)0 : _assert(#EXPRESSION, __FILE__, __LINE__))
