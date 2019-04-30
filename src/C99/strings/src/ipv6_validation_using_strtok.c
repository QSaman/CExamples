#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/*
 * 
 * Note that the following use of sscanf doesn't work. For example for ipv6_str = "::1", 
 * it returns 1 and all tokens[i] are null. If ipv6_str = "1::", tokens[0] is 1 and the
 * rest are null.
 * 
 *char tokens[8][5] = {'\0'};	//the maximum value for tokens[i] is ffff
 * char ch;
 *int cnt; 
	cnt = sscanf(ipv6_str, "%4[^:]:%4[^:]:%4[^:]:%4[^:]:%4[^:]:%4[^:]:%4[^:]:%4[^:]%c",
		         tokens[0], tokens[1], tokens[2], tokens[3], tokens[4], tokens[5],
		         tokens[6], tokens[7], &ch);
 **/ 

bool ipv6_validate_token(const char* ipv6_str_all, char* ipv6_str, long int ipv4[], int* token_count, const int max_token_count)
{
	char* token_str;
	*token_count = 0;

	for (token_str = strtok(ipv6_str, ":"); token_str != NULL && *token_count < max_token_count; token_str = strtok(NULL, ":"))
	{
		char * next;
		long int token = strtol(token_str, &next, 16);
		if (*next != '\0')
		{
			printf("%s has invalid token '%s'\n", ipv6_str_all, token_str);
			return false;
		}
		if (token_str[0] == '+' || token_str[0] == '-')
		{
			printf("%s has invalid token '%s'\n", ipv6_str_all, token_str);
			return false;
		}
		if (token < 0 || token > 65535)
		{
			printf("%s has invalid token '%s': Invalid range\n", ipv6_str_all, token_str);
			return false;
		}
		ipv4[(*token_count)++] = token;
	}
	if (token_str != NULL)
	{
		printf("%s has invalid number of tokens. It has at least %i tokens.\n", ipv6_str_all, *token_count + 1);
		return false;
	}
	return true;
}

bool free_buffer(char* buffer)
{
	free(buffer);
	buffer = NULL;
	return true;
}

bool ipv6_validation(const char* ipv6_str)
{
	long int ipv6[8] = {0};
	int left_tokens_count = 0;	//Number of tokens before ::
	int right_tokens_count = 0;	//Number of tokens after ::
	char* token;
	const size_t len = strlen(ipv6_str);
	char* str = (char*)malloc(len + 1);
	
	strcpy(str, ipv6_str);
	char* empty_token_str = strstr(str, "::");
	if (empty_token_str == NULL)
	{
		bool res = ipv6_validate_token(ipv6_str, str, ipv6, &left_tokens_count, 8);
		if (res)
		{
			printf("%s (%li, %li, %li, %li, %li, %li, %li, %li) is a valid IPv6 address\n",
				   ipv6_str, ipv6[0], ipv6[1], ipv6[2], ipv6[3], ipv6[4], ipv6[5], ipv6[6], ipv6[7]);
		}
		free_buffer(str);
		return res;
	}
	
	if (strstr(empty_token_str + 1, "::") != NULL)
	{
		printf("%s has invalid number of ::\n", ipv6_str);
		free_buffer(str);
		return false;
	}
	*empty_token_str = '\0';
	if (!ipv6_validate_token(ipv6_str, str, ipv6, &left_tokens_count, 8) && free_buffer(str))
		return false;
	if (left_tokens_count > 7)	//Since we have a :: the left side should have at most 7 tokens.
	{
		printf("%s has invalid number of tokesn. At least %i\n", ipv6_str, left_tokens_count + 1);
		free_buffer(str);
		return false;
	}
	if (!ipv6_validate_token(ipv6_str, empty_token_str + 1, ipv6 + left_tokens_count, &right_tokens_count, 8 - left_tokens_count) && free_buffer(str))
		return false;
	int pad_cnt = 8 - left_tokens_count - right_tokens_count;
	int total = left_tokens_count + right_tokens_count + pad_cnt;
	if (total != 8)
	{
		printf("%s has invalid number of tokesn: %i", ipv6_str, total);
		free_buffer(str);
		return false;
	}
	memmove(ipv6 + left_tokens_count + pad_cnt, ipv6 + left_tokens_count, right_tokens_count);
	for (int i = 0; i < pad_cnt; ++i)
		ipv6[left_tokens_count + i] = 0;
	printf("%s (%li, %li, %li, %li, %li, %li, %li, %li) is a valid IPv6 address\n",
		   ipv6_str, ipv6[0], ipv6[1], ipv6[2], ipv6[3], ipv6[4], ipv6[5], ipv6[6], ipv6[7]);
	free_buffer(str);
	return true;
}

int main(void)
{
	ipv6_validation("ff:ff:ff:ff:ff:ff:ff:ff");
	ipv6_validation("::1");
	ipv6_validation("1::1");
	ipv6_validation("1::ff");
	ipv6_validation("1:::ff");
	ipv6_validation("ff:ff:ff:ff:ff:ff:ff:ff:ff");
	ipv6_validation("ff:ff:ff:ff:ff:ff:ff:ff::ff");
	ipv6_validation("::+1");
	ipv6_validation("::-1");
}
