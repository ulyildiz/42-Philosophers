/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:34:32 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/04/17 23:07:35 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include <stdio.h>
#include <unistd.h>

void	print_status(t_flags status, int i, t_dining *tbl)
{
	size_t	time;

	safe_mutex(&tbl->print, LOCK, tbl);
	time = calc_current_ms_time() - tbl->begin_time;
	if (status == R_FORK && checking_flag(&tbl->waiting, &tbl->d_or_a,
			tbl) == ALIVE)
		printf("|%lu| - %d. philosopher's has taken a fork.(right)\n", time, i);
	else if (status == L_FORK && checking_flag(&tbl->waiting, &tbl->d_or_a,
			tbl) == ALIVE)
		printf("|%lu| - %d. philosopher's has taken a fork.(left)\n", time, i);
	else if (status == SLEEPING && checking_flag(&tbl->waiting, &tbl->d_or_a,
			tbl) == ALIVE)
		printf("|%lu| - %d. philosopher's sleeping.\n", time, i);
	else if (status == EATING && checking_flag(&tbl->waiting, &tbl->d_or_a,
			tbl) == ALIVE)
		printf("|%lu| - %d. philosopher's eating.\n", time, i);
	else if (status == THINKING && checking_flag(&tbl->waiting, &tbl->d_or_a,
			tbl) == ALIVE)
		printf("|%lu| - %d. philosopher's thinking.\n", time, i);
	else if (status == DEAD)
		printf("|%lu| - %d. philosopher's died.\n", time, i);
	safe_mutex(&tbl->print, UNLOCK, tbl);
}

void	err_mang(int flag)
{
	if (flag == 0)
		write(2, "Your input need to be an positive integer type's value.\n", 56);
	else if (flag == 1)
		write(2, "There is a problem while allocating memory.\n", 44);
	else if (flag == 2)
		write(2, "There is a problem about mutexes.\n", 34);
	else if (flag == 3)
		write(2, "There is a problem while creating or while waiting thread.\n", 59);
}
