#include "functions.h"

int	checking_flag(pthread_mutex_t *mtx, size_t *flag, t_dining *tbl)
{
	size_t	i;

	safe_mutex(mtx, LOCK, tbl);
	i = *flag;
	safe_mutex(mtx, UNLOCK, tbl);
	return (i);
}

void	set_safe(pthread_mutex_t *mtx, size_t value, size_t *dst) // TABLE'I GETİR
{
	pthread_mutex_lock(mtx);
	*dst = value;
	pthread_mutex_unlock(mtx);
}

void	wait_all(t_dining *table)
{
	while (checking_flag(&table->waiting, &table->flag, table))
		;
}


void	kinda_usleep(size_t ms, t_dining *table)
{
	size_t	start;
	size_t	current;

	start = calc_current_ms_time();
	while (calc_current_ms_time() - start < ms)
	{
		/*if ()
			break ;*/
		
	}
}
