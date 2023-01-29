#include <stdio.h>
#include <string.h>

#ifndef __MINIUNIT_H__
#define __MINIUNIT_H__

#define MU_SUCCESS 0

#define mu_start() int __mu_first_failure_line_number_or_0 = MU_SUCCESS

#define mu_check(condition) do{ \
	if((condition) == false && __mu_first_failure_line_number_or_0 == 0) {\
		__mu_first_failure_line_number_or_0 = __LINE__; \
	}\
} while(false)

#define mu_run(function) do { \
	int output = function(); \
	if (output != 0) { \
		printf("\x1b[31mTest failed: %s at line %d\x1b[0m.\n", #function, output); \
	} else { \
		printf("Test passed: %s\n", #function); \
	} \
} while(false)

#define mu_end() return __mu_first_failure_line_number_or_0

#endif /* end of include guard: __MINIUNIT_H__ */
