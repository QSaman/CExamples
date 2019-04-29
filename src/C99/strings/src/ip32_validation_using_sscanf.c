#include <stdio.h>
#include <stdbool.h>	//To use bool in C

bool validate_ip32(const char* ip32_str)
{
	int ip32[4] = {0};
	char ch;
	int cnt = sscanf(ip32_str, "%i.%i.%i.%i%c", &ip32[0], &ip32[1], &ip32[2], &ip32[3], &ch);
	if (cnt == EOF || cnt != 4)
	{
		printf("%s is not a valid IP32. sscanf returned %i\n", ip32_str, cnt);
		return false;
	}

	for (int i = 0; i < 4; ++i)
	{
		if (ip32[i] < 0 || ip32[i] > 255)
		{
			printf("%s is not a valid IP32. %i is out of range\n", ip32_str, ip32[i]);
			return false;
		}
	}
	printf("%s (%i, %i, %i, %i) is a valid IP32.\n", ip32_str, ip32[0], ip32[1], ip32[2], ip32[3]);
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
