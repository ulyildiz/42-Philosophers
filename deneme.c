#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "defines.h"
#include <sys/time.h>

int	main(void)
{
	/*pthread_mutex_t	*a;
	char			*opaque_ptr;

	// Allocate memory for the mutex
	// Initialize the mutex
	pthread_mutex_init(a, NULL);
	// Access the __opaque array byte-by-byte
	opaque_ptr = (char *)&(a->__opaque);
	pthread_mutex_lock(a);
	pthread_mutex_unlock(a);
	printf("Contents of __opaque array: ");
	for (size_t i = 0; i < sizeof(a->__opaque); ++i)
	{
		printf("%d ", opaque_ptr[i]);
	}
	printf("\n");
	// Free memory allocated for the mutex*/
	/*t_node *tmp;
	t_node *a;
	a = malloc(sizeof(t_node));
	int i = 0;
	while (++i < 200)
	{
		tmp = malloc(sizeof(t_node));
		a->next = tmp;
		tmp->prev = a;
		a = a->next;
		
	}
	struct timeval	time;
	struct timeval	time2;
	gettimeofday(&time, NULL);
	while (a)
	{
		if (i == 0)
			return (printf("s"), 0);
		printf("a\n");
		a = a->prev;
	}
	gettimeofday(&time2, NULL);
	printf("%f\n", (time2.tv_sec * 1000 + time2.tv_usec * 0.001)-(time.tv_sec * 1000 + time.tv_usec * 0.001));*/
	pthread_mutex_t *a;
	a = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(a, NULL);
	free(a);
	return (0);
}


//döngüde value geçmesini dene