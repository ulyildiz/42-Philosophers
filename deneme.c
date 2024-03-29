#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *s(void *a)
{
	printf("2\n");
	if (a)
		exit(1);
	usleep(10000);
	return (NULL);
}

int main()
{
	pthread_t t;
	printf("a\n");
	pthread_create(&t, NULL, &s, NULL);
	printf("b\n");
	pthread_join(t, NULL);
	printf("c\n");
}