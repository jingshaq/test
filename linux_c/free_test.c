#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// error free and set NULL
void my_free0(char *p)
{
	printf("p=%p\n", p);
	free(p);
	p = NULL;
}

// error free and set NULL
void my_free1(char **p)
{
	char *ptr = *p;
	printf("ptr=%p\n", ptr);
	free(ptr);
	ptr = NULL;
}

// success free and set NULL
void my_free2(char **p)
{
	printf("*p=%p\n", *p);
	free(*p);
	*p = NULL;
}

int main(void)
{
	char *value = (char *)malloc(100);
	printf("value=%p\n", value);
	my_free2(&value);
	printf("value=%p\n", value);
	return 0;
}
