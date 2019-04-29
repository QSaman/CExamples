#include <stdio.h>
#include <stdbool.h>	//To use bool in C
#include <ctype.h>
#include <stdlib.h>

bool validate_ip32(const char* ip32_str)
{
	char token[4][5] = {'\0'};	//maximum token[i] can be 255 (decminal), 0xff (hex), 0773 (oct)
	long int ip32[4] = {0};
	char ch;
	int cnt = sscanf(ip32_str, "%[^.].%[^.].%[^.].%[^.]%c", token[0], token[1], token[2], token[3], &ch);
	if (cnt == EOF || cnt != 4)
	{
		printf("%s is not a valid IP32. sscanf returned %i\n", ip32_str, cnt);
		return false;
	}

	for (int i = 0; i < 4; ++i)
	{
		char* next;
		if (!isdigit(token[i][0]))
		{
			printf("%s is not a valid IP32. token '%s' is invalid. It doesn't start with a digit.\n", ip32_str, token[i]);
			return false;

		}
		long int num = strtol(token[i], &next, 0);
		if (*next != '\0')
		{
			printf("%s is not a valid IP32. token '%s' is invalid\n", ip32_str, token[i]);
			return false;
		}

		if (num < 0 || num > 255)
		{
			printf("%s is not a valid IP32. %li (%ld) is not in range\n", ip32_str, num, num);
			return false;
		}

		ip32[i] = num;
	}

	printf("%s (%li, %li, %li, %li) is a valid ip32 address\n", ip32_str, ip32[0], ip32[1], ip32[2], ip32[3]);
	return true;
}

int main(void)
{
	printf("EOF: %i\n", EOF);
	validate_ip32("192.168.0.1");	//sscanf return 4
	validate_ip32("010.0xf.0.1");	//sscanf return 4
	validate_ip32("080.0xf.0.1");	//Note in oct every digit should be between 0 and 7. sscanf return 1
	validate_ip32("192.168.0.0.10");	//sscanf return 5
	validate_ip32("192.168");	//sscanf return 2
	validate_ip32("+192.168.0.1");	//sscanf return 4. Altough it starts with '+', it's a valid IP32!
	validate_ip32("-192.168.0.1");	//sscanf return 4
	validate_ip32("192x43.168.0.1");	//sscanf return 1
	validate_ip32("x192.168.0.1");	//sscanf return 0
	validate_ip32("");	//sscanf return -1 (EOF)
}
