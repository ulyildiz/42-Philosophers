#include "defines.h"

int	checking_flag(pthread_mutex_t *mtx, size_t *flag)
{
	size_t	i;

	pthread_mutex_lock(mtx);
	i = *flag;
	pthread_mutex_unlock(mtx);
	return (i);
}

void	set_safe(pthread_mutex_t *mtx, size_t value, size_t *dst)
{
	pthread_mutex_lock(mtx);
	*dst = value;
	pthread_mutex_unlock(mtx);
}

void	wait_all(t_dining *table)
{
	while (checking_flag(&table->waiting, &table->flag))
		;
}
