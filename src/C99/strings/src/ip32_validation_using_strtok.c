#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>	//To use bool in C

bool strtok_example(const char* ip32_str)
{
	const size_t len = strlen(ip32_str);
	char* str = (char*)malloc(len + 1);

	if (str == NULL)
	{
		perror("Cannot allocate memory");
		return false;
	}

	long int ip32[4] = {0};

	strncpy(str, ip32_str, len + 1);
	char* token = strtok(str, ".");
	for (int i = 0; token != NULL; token = strtok(NULL, "."), ++i)
	{
		char* next;
		long int num = strtol(token, &next, 0);
		if (*next != '\0')
		{
			free(str);
			return false;
		}
		ip32[i] = num;
	}
	printf("%ld.%ld.%ld.%ld is a valid ip32 address\n", ip32[0], ip32[1], ip32[2], ip32[3]);
	free(str);
	return true;
}

int main(void)
{
	if (!strtok_example("192.168.0.1"))
		perror("Invalid IP32");
	if (!strtok_example("010.0xf.0.1"))
		perror("Invalid IP32");
	if (!strtok_example("080.0xf.0.1"))
		perror("Invalid IP32");
}
