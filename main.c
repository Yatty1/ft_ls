#include <time.h>
#include <stdio.h>

int		main()
{
	time_t hoge;
	time(&hoge);
	printf("%ld\n", hoge);
	return (0);
}
