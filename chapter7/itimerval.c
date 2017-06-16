#include <stdio.h>

int main()
{
	printf("%d : %d \n", 60500/1000, 60500%1000*1000L);
	printf("%d : %d \n", 240250/1000, 240250%1000*1000L);
	putchar('\n');	
	printf("%d \n", 60500%1000);
	printf("%d \n", 240250%1000);
}
