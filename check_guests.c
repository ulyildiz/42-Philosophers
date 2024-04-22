/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_guests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:34:05 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/04/18 10:51:50 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include <unistd.h>

static int	check_dead(t_node *current_philo)
{
	if (checking_flag(&current_philo->m_status, &current_philo->status) == FULL)
		return (0);
	if (calc_current_ms_time() - checking_flag(&current_philo->p_set,
			&current_philo->last_eat) >= current_philo->tbl->time_die)
		return (set_safe(&current_philo->m_status, DEAD,
				&current_philo->status), 1);
	return (0);
}

void	*check_guests(void *a)
{
	t_dining	*table;
	t_node		*tmp;

	table = (t_dining *)a;
	tmp = table->philo_node;
	while (1)
		if (checking_flag(&table->set, &table->i) == table->philo_nbr)
			break ;
	while (checking_flag(&table->set, &table->i))
	{
		if (check_dead(tmp))
		{
			set_safe(&table->waiting, DEAD, &table->d_or_a);
			print_status(DEAD, tmp->index, table);
			return (NULL);
		}
		usleep(20);
		tmp = tmp->next;
	}
	return (NULL);
}
