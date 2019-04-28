#include <stdio.h>
#include <stdlib.h>

void realloc_example(int n)
{
	int* buffer = NULL;
	int* tmp;
	for (int i = 0; i < n; ++i)
	{
		tmp = (int*) realloc(buffer, sizeof(int));
		if (tmp == NULL)
		{
			perror("Cannot allocate memory");
			free(buffer);
			return;
		}
		buffer = tmp;
		buffer[i] = i;
	}
	for (int i = 0; i < n; ++i)
		printf("%d ", i);
	puts("");
	free(buffer);
}

int main(void)
{
	realloc_example(5);
}
