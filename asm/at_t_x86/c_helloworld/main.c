#include <stdio.h>

int  main(int argc, char *argv[]) 
{
	int in = 100;
	int out = 0;
	__asm__ __volatile__ ("movl %1,%0" : "=r" (out) : "m" (in));
	printf("out = %d\n",out);
	
	int a = 1, b = 2, c = 3;
    __asm__ __volatile__(
			"movl %1, %%eax;\
			movl %2, %%ecx;\
			addl %0, %%eax;\
			addl %0, %%ecx"
            :"=m"(c)/* output */
            :"r"(a),"r"(b) /* input */
            );
	printf("%d + %d = %d\n", a, b, c);
	return 0; 
}
