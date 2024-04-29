
#include "defines.h"
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

int	main(void)
{
	char			*opaque_ptr;
	t_node			*a;
	int				i;
	struct timeval	start;
	struct timeval	current;


	opaque_ptr = malloc(10);
	if (opaque_ptr)
		write (1, "var\n", 4);
	if (!opaque_ptr)
		write(1, "yok\n", 4);
	free(opaque_ptr);
	if (opaque_ptr)
		write (1, "hala var\n", 9);
	if (!opaque_ptr)
		write(1, "artık yok\n", 10);
	/*pthread_mutex_t	*a;
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
	a = malloc(sizeof(t_node));
	i = 0;
	while (++i < 200)
	{
		tmp = malloc(sizeof(t_node));
		a->next = tmp;
		tmp->prev = a;
		a = a->next;
	}*/
	/*gettimeofday(&start, NULL);
	usleep(500000);
	gettimeofday(&current, NULL);
	printf("usleep = %f\n", (current.tv_sec * 1000 + current.tv_usec * 0.001)
		- (start.tv_sec * 1000 + start.tv_usec * 0.001));
	gettimeofday(&start, NULL);
	kinda_usleep(500, NULL);
	gettimeofday(&current, NULL);
	printf("%f\n", (current.tv_sec * 1000 + current.tv_usec * 0.001)
		- (start.tv_sec * 1000 + start.tv_usec * 0.001));
	;*/
	//	pthread_mutex_t *a;
	/*a = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(a, NULL);
	printf("%d\n", pthread_mutex_destroy(a));
	free(a);
	*/
	return (0);
}

// döngüde value geçmesini dene