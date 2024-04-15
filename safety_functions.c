// mutex ve thread düzgün hata kontrolleri
#include "functions.h"
#include <stdlib.h>

static void	mutex_error(int check, t_flags flag, t_dining *tbl)
{
	if (check)
	{
		err_mang(2);
		if (flag != DESTROY)
			clean_mutex(tbl);
		clean_node(tbl);
		exit(1);
	}
}

static void	thread_error(int check, t_flags flag, t_dining *tbl)
{
	if (check)
	{
		if (flag)
			;
		err_mang(3);
		clean_mutex(tbl);
		clean_node(tbl);
		exit(1);
	}
}

void	safe_mutex(pthread_mutex_t *mtx, t_flags flag, t_dining* tbl) // mutex destroyları mutex lockluyken ve oluşmamışken çalışacak şekilde çağırma
{
	if (flag == UNLOCK)
		mutex_error(pthread_mutex_unlock(mtx), flag, tbl);
	else if (flag == LOCK)
		mutex_error(pthread_mutex_lock(mtx), flag, tbl);
	else if (flag == INIT)
		mutex_error(pthread_mutex_init(mtx, NULL), flag, tbl);
	else if (flag == DESTROY)
		mutex_error(pthread_mutex_destroy(mtx), flag, tbl);
}

void	safe_thread(pthread_t *thread, t_flags flag, t_node *philo, void *(*func)(void *))
{
	if (flag == CREATE)
		thread_error(pthread_create(thread, NULL, func, philo), flag, philo->tbl);
	else if (flag == JOIN)
		thread_error(pthread_join(*thread, NULL), flag, philo->tbl);
}
