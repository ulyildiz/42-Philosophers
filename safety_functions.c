/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safety_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:34:34 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/04/18 16:14:31 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include <stdlib.h>

static void	mutex_error(int check, t_flags flag, t_dining *tbl)
{
	if (check)
	{
		err_mang(2);
		clean_node(tbl, tbl->philo_nbr);
		exit(1);
	}
}

static void	thread_error(int check, t_flags flag, t_dining *tbl)
{
	if (check)
	{
		if (flag)
			flag = 0;
		err_mang(3);
		clean_node(tbl, tbl->philo_nbr);
		exit(1);
	}
}

void	safe_mutex(pthread_mutex_t *mtx, t_flags flag, t_dining *tbl)
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

void	safe_thread(pthread_t *thread, t_flags flag, t_node *philo,
		void *(*func)(void *))
{
	if (flag == CREATE)
	{
		thread_error(pthread_create(thread, NULL, func, philo), flag,
			philo->tbl);
		pthread_detach(thread);
	}
	else if (flag == JOIN)
		thread_error(pthread_join(*thread, NULL), flag, philo->tbl);
}
