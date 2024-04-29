#include <stdio.h>
#include <pthread.h>

void	c()
{
	int i;
	printf("%p\n", &i);

}

void	*d(void	*s)
{
	int a;
	c();
	return (NULL);
}

int main()
{
	pthread_t a;
	pthread_t b;
	pthread_create(&a, NULL, &d, NULL);
	pthread_create(&b, NULL, &d, NULL);

	pthread_join(a, NULL);
	pthread_join(b, NULL);
}