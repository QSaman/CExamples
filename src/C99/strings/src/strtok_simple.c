#include <stdio.h>
#include <assert.h>
#include <string.h>

void f1()
{
	char* buffer[2];
	char str[] = "1::1";
	int i;
	char* token;
	for (i = 0, token = strtok(str, ":"); token != NULL; token = strtok(NULL, ":"), ++i)
	{
		buffer[i] = token;
	}
	assert(i == 2);
	assert(strcmp(buffer[0], "1") == 0 && strcmp(buffer[1], "1") == 0);
}

void f2()
{
	char str[] = "::";
	int i;
	char* token;
	for (i = 0, token = strtok(str, ":"); token != NULL; token = strtok(NULL, ":"), ++i)
	{
	}
	assert(i == 0);
}

void f3()
{
	char* buffer[3];
	char str[] = "123:456:78";
	int i;
	char* token;
	for (i = 0, token = strtok(str, ":"); token != NULL; token = strtok(NULL, ":"), ++i)
	{
		buffer[i] = token;
	}
	assert(i == 3);
	assert(strcmp(buffer[0], "123") == 0 && strcmp(buffer[1], "456") == 0 && strcmp(buffer[2], "78") == 0);
}
int main(void)
{
	f1();
	f2();
	f3();
}
