#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	pthread_mutex_t	*a;
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
	// Free memory allocated for the mutex
	return (0);
}


//döngüde value geçmesini dene