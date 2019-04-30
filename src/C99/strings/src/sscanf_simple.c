#include <stdio.h>
#include <assert.h>
#include <string.h>


void f1()
{
	char buffer[3][10] = {'\0'};
	
	int cnt = sscanf(":::", "%[^:]:%[^:]:%[^:]", buffer[0], buffer[1], buffer[2]);
	assert(cnt == 0);
	for (int i = 0; i < 3; ++i)
	assert(buffer[i][0] == '\0');
}

void f2()
{
	char buffer[3][10] = {'\0'};
	
	int cnt = sscanf("23:::", "%[^:]:%[^:]:%[^:]", buffer[0], buffer[1], buffer[2]);
	assert(cnt == 1);
	assert(strcmp("23", buffer[0]) == 0);
	for (int i = 1; i < 3; ++i)
	assert(buffer[i][0] == '\0');
}

void f3()
{
	char buffer[3][10] = {'\0'};
	
	int cnt = sscanf(":23::", "%[^:]:%[^:]:%[^:]", buffer[0], buffer[1], buffer[2]);
	assert(cnt == 0);
	for (int i = 0; i < 3; ++i)
	assert(buffer[i][0] == '\0');
}

void f4()
{
	int buffer[4] = {0};
	char ch;
	
	int cnt = sscanf("192.168.0.1.20", "%i.%i.%i.%i%c", &buffer[0], &buffer[1], &buffer[2], &buffer[3], &ch);
	assert(cnt == 5);
	assert(buffer[0] == 192 && buffer[1] == 168 && buffer[2] == 0 && buffer[3] == 1 && ch == '.');
}

void f5()
{
	int num = 0;
	int cnt = sscanf("", "%i", &num);
	assert(cnt == EOF);
}

void f6()
{
	int n1, n2, n3;	//n1 is decima, n2 is hex and n3 is octal
	int cnt = sscanf("100, 0xff, 010", "%i, %i, %i", &n1, &n2, &n3);
	assert(cnt == 3);
	assert(n1 == 100 && n2 == 0xff && n3 == 010);
	assert(n1 == 100 && n2 == 255 && n3 == 8);
}

void f7()
{
	int n1, n2, n3;	//all numbers are decimal
	int cnt = sscanf("100, 010, 0xff", "%d, %d, %d", &n1, &n2, &n3);
	assert(cnt == 3);
	assert(n1 == 100 && n2 == 10 && n3 == 0);
}

int main(void)
{
	f1();
	f2();
	f3();
	f4();
	f5();
	f6();
	f7();
}
