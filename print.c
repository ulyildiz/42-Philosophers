/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:34:32 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/04/17 12:40:02 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include <stdio.h>

void	print_status(t_flags status, int i, t_dining *tbl)
{
	size_t	time;

	safe_mutex(&tbl->print, LOCK, tbl);
	time = calc_current_ms_time() - tbl->begin_time;
	if (status == R_FORK && checking_flag(&tbl->waiting, &tbl->d_or_a, tbl) == ALIVE)
		printf("|%lu| - %d. philosopher's has taken a fork.(right)\n", time, i);
	else if (status == L_FORK && checking_flag(&tbl->waiting, &tbl->d_or_a, tbl) == ALIVE)
		printf("|%lu| - %d. philosopher's has taken a fork.(left)\n", time, i);
	else if (status == SLEEPING && checking_flag(&tbl->waiting, &tbl->d_or_a, tbl) == ALIVE)
		printf("|%lu| - %d. philosopher's sleeping.\n", time, i);
	else if (status == EATING && checking_flag(&tbl->waiting, &tbl->d_or_a, tbl) == ALIVE)
		printf("|%lu| - %d. philosopher's eating.\n", time, i);
	else if (status == THINKING && checking_flag(&tbl->waiting, &tbl->d_or_a, tbl) == ALIVE)
		printf("|%lu| - %d. philosopher's thinking.\n", time, i);
	else if (status == DEAD)
		printf("|%lu| - %d. philosopher's died.\n", time, i);
	safe_mutex(&tbl->print, UNLOCK, tbl);
}

void	err_mang(int flag) // write daha mı mantıklı?
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
/**/