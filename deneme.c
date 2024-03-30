#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

void	*s(void *a)
{
	printf("2\n");
	if (a)
		exit(1);
	return (NULL);
}

int	main(void)
{
	struct timeval a;
	gettimeofday(&a, NULL);
	pthread_t t;
	pthread_t t1;
	printf("a\n");
	pthread_create(&t, NULL, &s, NULL);
	pthread_create(&t1, NULL, &s, NULL);
	printf("b\n");
	pthread_join(t, NULL);
	printf("0.c\n");
	pthread_join(t1, NULL);
	printf("c\n");
	int a = 5;
	//while(a == 5);
}