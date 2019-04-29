#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>	//To use bool in C

#define print(x) printf("%s: %s\n", #x, x)

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

	int i;
	for (i = 0; i < 4 && token != NULL; token = strtok(NULL, "."), ++i)
	{
		char* next;
		long int num = strtol(token, &next, 0);
		if (*next != '\0')
		{
			printf("%s is not a valid IP32. token '%s' is invalid\n", ip32_str, token);
			free(str);
			return false;
		}

		if (num < 0 || num > 255)
		{
			printf("%s is not a valid IP32. %li (%ld) is not in range\n", ip32_str, num, num);
			free(str);
			return false;
		}

		ip32[i] = num;
	}
	if (i != 4)
	{
		printf("%s is not a valid IP32. token numbers: %i\n", ip32_str, i);
		free(str);
		return false;
	}
	if (token != NULL)
	{
		printf("%s is not a valid IP32. It has more than 4 tokens\n", ip32_str);
		return false;
	}
	printf("%ld.%ld.%ld.%ld is a valid ip32 address\n", ip32[0], ip32[1], ip32[2], ip32[3]);
	free(str);
	return true;
}

int main(void)
{
	strtok_example("192.168.0.1");
	strtok_example("010.0xf.0.1");
	strtok_example("080.0xf.0.1");	//Note in oct every digit should be between 0 and 7.
	strtok_example("192.168.0.0.10");
	strtok_example("192.168");
}
