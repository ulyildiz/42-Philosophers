#include "defines.h"
#include <stdio.h> 

void	print_status(t_flags status, int i, pthread_mutex_t *print)
{
	pthread_mutex_lock(print);
	if (status == R_FORK)
		printf("%d. philosopher's has taken a fork.(right)\n", i);
	else if (status == L_FORK)
		printf("%d. philosopher's has taken a fork.(left)\n", i);
	else if (status == SLEEPING)
		printf("%d. philosopher's sleeping.\n", i);
	else if (status == EATING)
		printf("%d. philosopher's eating.\n", i);
	else if (status == THINKING)
		printf("%d. philosopher's thinking.\n", i);
	pthread_mutex_unlock(print);
}

void	err_mang(int flag) //write daha mı mantıklı?
{
	if (flag == 0)
		printf("Your input need to be an positive integer type's value.\n");
	else if (flag == 1)
		printf("There is a problem while allocating memory.\n");
	else if (flag == 2)
		printf("There is a problem about mutexes.\n");
	else if (flag == 3)
		printf("There is a problem while creating thread or pthread_join function.\n");
}
