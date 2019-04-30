#include <stdio.h>
#include <stdbool.h>	//To use bool in C

bool validate_ipv4(const char* ipv4_str)
{
	int ipv4[4] = {0};
	char ch;
	int cnt = sscanf(ipv4_str, "%i.%i.%i.%i%c", &ipv4[0], &ipv4[1], &ipv4[2], &ipv4[3], &ch);
	if (cnt == EOF || cnt != 4)
	{
		printf("%s is not a valid ipv4. sscanf returned %i\n", ipv4_str, cnt);
		return false;
	}

	for (int i = 0; i < 4; ++i)
	{
		if (ipv4[i] < 0 || ipv4[i] > 255)
		{
			printf("%s is not a valid ipv4. %i is out of range\n", ipv4_str, ipv4[i]);
			return false;
		}
	}
	printf("%s (%i, %i, %i, %i) is a valid ipv4.\n", ipv4_str, ipv4[0], ipv4[1], ipv4[2], ipv4[3]);
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
	validate_ipv4("+192.168.0.1");	//sscanf return 4. Altough it starts with '+', it's a valid ipv4! See ipv4_validation_using_sscanfv2.c for a solution
	validate_ipv4("-192.168.0.1");	//sscanf return 4
	validate_ipv4("192x43.168.0.1");	//sscanf return 1
	validate_ipv4("x192.168.0.1");	//sscanf return 0
	validate_ipv4("");	//sscanf return -1 (EOF)
	validate_ipv4("192192.168.0.0");	//sscanf return 1
}
