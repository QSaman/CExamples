#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <limits.h>

void strtol_example()
{
	char* next = NULL;
	long int num;

	num = strtol("123", &next, 0);	//decimal number
	assert(*next == '\0' && num == 123);

	num = strtol("-123", &next, 0);
	assert(*next == '\0' && num == -123);

	num = strtol("-0xf", &next, 0);	//hex number
	assert(*next == '\0' && num == -15);

	num = strtol("0xf", &next, 0);
	assert(*next == '\0' && num == 15);

	num = strtol("07", &next, 0);	//oct number
	assert(*next == '\0' && num == 7);

	num = strtol("010", &next, 0);
	assert(*next == '\0' && num == 8);

	num = strtol("a23", &next, 0);
	assert(*next == 'a' && num == 0);

	num = strtol("23a", &next, 0);
	assert(*next == 'a' && num == 23);

	num = strtol("9999999999999999999999999999", &next, 0);
	assert(num == LONG_MAX && errno == ERANGE);
}

int main(void)
{
	strtol_example();
}
