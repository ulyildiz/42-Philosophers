#include "defines.h"

int	checking_flag(pthread_mutex_t *mtx, size_t *flag)
{
	int	i;

	pthread_mutex_lock(mtx);
	i = *flag;
	pthread_mutex_unlock(mtx);
	return (i);
}

void	set_safe(pthread_mutex_t *mtx, int value, size_t *dst)
		// HER ZAMAN INT DEĞİLSE DEĞİŞTİR
{
	pthread_mutex_lock(mtx);
	*dst = value;
	pthread_mutex_unlock(mtx);
}

void	wait_all(t_dining *table)
{
	while (checking_flag(&table->waiting, &table->eat_count) == -1)
		;
}