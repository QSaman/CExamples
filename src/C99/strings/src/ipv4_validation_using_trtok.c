#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>	//To use bool in C
#include <ctype.h>

#define print(x) printf("%s: %s\n", #x, x)

bool validate_ipv4(const char* ipv4_str)
{
	const size_t len = strlen(ipv4_str);
	char* str = (char*)malloc(len + 1);

	if (str == NULL)
	{
		perror("Cannot allocate memory");
		return false;
	}

	long int ipv4[4] = {0};

	strncpy(str, ipv4_str, len + 1);
	char* token = strtok(str, ".");

	int i;
	for (i = 0; i < 4 && token != NULL; token = strtok(NULL, "."), ++i)
	{
		char* next;
		if (!isdigit(*token))
		{
			printf("%s is not a valid ipv4. token '%s' is invalid. It doesn't start with a digit.\n", ipv4_str, token);
			free(str);
			return false;

		}
		long int num = strtol(token, &next, 0);
		if (*next != '\0')
		{
			printf("%s is not a valid ipv4. token '%s' is invalid\n", ipv4_str, token);
			free(str);
			return false;
		}

		if (num < 0 || num > 255)
		{
			printf("%s is not a valid ipv4. %li (%ld) is not in range\n", ipv4_str, num, num);
			free(str);
			return false;
		}

		ipv4[i] = num;
	}
	if (i != 4)
	{
		printf("%s is not a valid ipv4. token numbers: %i\n", ipv4_str, i);
		free(str);
		return false;
	}
	if (token != NULL)
	{
		printf("%s is not a valid ipv4. It has more than 4 tokens\n", ipv4_str);
		return false;
	}
	printf("%s (%li, %li, %li, %li) is a valid ipv4 address\n", ipv4_str, ipv4[0], ipv4[1], ipv4[2], ipv4[3]);
	free(str);
	return true;
}

int main(void)
{
	validate_ipv4("192.168.0.1");
	validate_ipv4("010.0xf.0.1");
	validate_ipv4("080.0xf.0.1");	//Note in oct every digit should be between 0 and 7.
	validate_ipv4("192.168.0.0.10");
	validate_ipv4("192.168");
	validate_ipv4("+192.168.0.1"); //Since it starts with a '+' character, it's not a valid ipv4
	validate_ipv4("-192.168.0.1");
	validate_ipv4("192x43.168.0.1");
	validate_ipv4("x192.168.0.1");
	validate_ipv4("");
	validate_ipv4("192192.168.0.0");
}
