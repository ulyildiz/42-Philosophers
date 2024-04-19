/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:33:56 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/04/17 14:22:40 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include <unistd.h>

size_t	checking_flag(pthread_mutex_t *mtx, size_t *flag, t_dining *tbl)
{
	size_t	i;

	safe_mutex(mtx, LOCK, tbl);
	i = *flag;
	safe_mutex(mtx, UNLOCK, tbl);
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
	while (!checking_flag(&table->waiting, &table->flag, table))
		;
}

void	increase_long(pthread_mutex_t *mutex, size_t *value)
{
	safe_mutex(mutex, LOCK, NULL);
	(*value)++;
	safe_mutex(mutex, UNLOCK, NULL);
}

void	kinda_usleep(size_t ms, t_dining *table)
{
	size_t	start;

	start = calc_current_ms_time();
	while (calc_current_ms_time() - start < ms)
	{
		if (checking_flag(&table->waiting, &table->d_or_a, table) != ALIVE)
			break ;
		usleep(5);
	}
}
