#include <stdio.h>
#include <stdbool.h>	//To use bool in C
#include <ctype.h>
#include <stdlib.h>

bool validate_ipv4(const char* ipv4_str)
{
	char token[4][5] = {'\0'};	//maximum token[i] can be 255 (decminal), 0xff (hex), 0773 (oct)
	long int ipv4[4] = {0};
	char ch;
	int cnt = sscanf(ipv4_str, "%4[^.].%4[^.].%4[^.].%4[^.]%c", token[0], token[1], token[2], token[3], &ch);
	if (cnt == EOF || cnt != 4)
	{
		printf("%s is not a valid ipv4. sscanf returned %i\n", ipv4_str, cnt);
		return false;
	}

	for (int i = 0; i < 4; ++i)
	{
		char* next;
		if (!isdigit(token[i][0]))
		{
			printf("%s is not a valid ipv4. token '%s' is invalid. It doesn't start with a digit.\n", ipv4_str, token[i]);
			return false;

		}
		long int num = strtol(token[i], &next, 0);
		if (*next != '\0')
		{
			printf("%s is not a valid ipv4. token '%s' is invalid\n", ipv4_str, token[i]);
			return false;
		}

		if (num < 0 || num > 255)
		{
			printf("%s is not a valid ipv4. %li (%ld) is not in range\n", ipv4_str, num, num);
			return false;
		}

		ipv4[i] = num;
	}

	printf("%s (%li, %li, %li, %li) is a valid ipv4 address\n", ipv4_str, ipv4[0], ipv4[1], ipv4[2], ipv4[3]);
	return true;
}

int main(void)
{
	printf("EOF: %i\n", EOF);
	validate_ipv4("192.168.0.1");	//sscanf return 4
	validate_ipv4("010.0xf.0.1");	//sscanf return 4
	validate_ipv4("080.0xf.0.1");	//Note in oct every digit should be between 0 and 7. sscanf return 1
	validate_ipv4("192.168.0.0.10");	//sscanf return 5
	validate_ipv4("192.168");	//sscanf return 2
	validate_ipv4("+192.168.0.1");	//sscanf return 4. Since it starts with a + character, it's invalid
	validate_ipv4("-192.168.0.1");	//sscanf return 4
	validate_ipv4("192x43.168.0.1");	//sscanf return 1
	validate_ipv4("x192.168.0.1");	//sscanf return 0
	validate_ipv4("");	//sscanf return -1 (EOF)
	validate_ipv4("192192.168.0.0");	//sscanf return 1
}
