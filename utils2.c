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

size_t	checking_flag(pthread_mutex_t *mtx, size_t *flag)
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

int	wait_all(t_dining *table)
{
	size_t	i;

	i = 0;
	while (i == 1 || i == 0)
	{
		i = checking_flag(&table->waiting, &table->flag);
		if (i == 1)
			return (0);
	}
	return (1);
}

void	increase_long(pthread_mutex_t *mtx, size_t *value)
{
	pthread_mutex_lock(mtx);
	(*value)++;
	pthread_mutex_unlock(mtx);
}

void	kinda_usleep(size_t ms, t_dining *table)
{
	size_t	start;

	start = calc_current_ms_time();
	while (calc_current_ms_time() - start < ms)
	{
		if (checking_flag(&table->waiting, &table->d_or_a) != ALIVE)
			break ;
		usleep(5);
	}
}
