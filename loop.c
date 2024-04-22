/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:33:59 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/04/22 13:00:35 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

static void	eat_and_sleep(t_node *philo)
{
	pthread_mutex_lock(philo->l);
	print_status(L_FORK, philo->index, philo->tbl);
	pthread_mutex_lock(philo->r);
	print_status(R_FORK, philo->index, philo->tbl);
	if (philo->tbl->eat_count == 0)
		kinda_usleep(philo->tbl->time_die + 3, philo->tbl);
	print_status(EATING, philo->index, philo->tbl);
	kinda_usleep(philo->tbl->time_eat, philo->tbl);
	set_safe(&philo->p_set, calc_current_ms_time(), &philo->last_eat);
	philo->eated++;
	if (philo->eated == philo->tbl->eat_count)
		return (pthread_mutex_unlock(philo->l),
			pthread_mutex_unlock(philo->r), set_safe(&philo->m_status, FULL,
				&philo->status));
	pthread_mutex_unlock(philo->l);
	pthread_mutex_unlock(philo->r);
	print_status(SLEEPING, philo->index, philo->tbl);
	kinda_usleep(philo->tbl->time_sleep, philo->tbl);
}

static void	*gods_lonely_man(void *a)
{
	t_node	*philo;

	philo = (t_node *)a;
	if (!wait_all(philo->tbl))
		return (pthread_detach(philo->philo_id),
			increase_long(&philo->tbl->set, &philo->tbl->detached), NULL);
	set_safe(&philo->p_set, calc_current_ms_time(), &philo->last_eat);
	increase_long(&philo->tbl->set, &philo->tbl->i);
	pthread_mutex_lock(philo->r);
	print_status(R_FORK, philo->index, philo->tbl);
	kinda_usleep(philo->tbl->time_die, philo->tbl);
	print_status(DEAD, philo->index, philo->tbl);
	pthread_mutex_unlock(philo->r);
	return (NULL);
}

void	*starting_section(void *a)
{
	t_node	*philo;

	philo = (t_node *)a;
	if (!wait_all(philo->tbl))
		return (pthread_detach(philo->philo_id),
			increase_long(&philo->tbl->set, &philo->tbl->detached), NULL);
	set_safe(&philo->p_set, calc_current_ms_time(), &philo->last_eat);
	increase_long(&philo->tbl->set, &philo->tbl->i);
	if (philo->index % 2)
		usleep(500);
	while (checking_flag(&philo->tbl->waiting, &philo->tbl->d_or_a) == ALIVE)
	{
		eat_and_sleep(philo);
		if (checking_flag(&philo->m_status, &philo->status) == FULL)
			return (NULL);
		print_status(THINKING, philo->index, philo->tbl);
		kinda_usleep(2, philo->tbl);
	}
	return (NULL);
}

static void	join(t_dining *table)
{
	size_t	i;

	i = 0;
	while (++i <= table->philo_nbr)
	{
		pthread_join(table->philo_node->philo_id, NULL);
		table->philo_node = table->philo_node->next;
	}
	set_safe(&table->set, 0, &table->i);
	if (table->philo_nbr > 1)
		pthread_join(table->owner, NULL);
}

int	invite_philo(t_dining *table)
{
	size_t	i;

	i = 0;
	if (table->philo_nbr == 1 && ++i)
	{
		if (pthread_create(&table->philo_node->philo_id, NULL, &gods_lonely_man,
				table->philo_node))
			return (set_safe(&table->waiting, 1, &table->flag), i);
	}
	else
	{
		while (++i <= table->philo_nbr)
		{
			if (pthread_create(&table->philo_node->philo_id, NULL,
					&starting_section, table->philo_node))
				return (set_safe(&table->waiting, 1, &table->flag), i);
			table->philo_node = table->philo_node->next;
		}
	}
	set_safe(&table->waiting, calc_current_ms_time(), &table->begin_time);
	if (table->philo_nbr > 1 && pthread_create(&table->owner, NULL,
			&check_guests, table))
		return (set_safe(&table->waiting, 1, &table->flag), i);
	set_safe(&table->waiting, -1, &table->flag);
	return (join(table), 0);
}
