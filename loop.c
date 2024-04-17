/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:33:59 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/04/17 14:27:21 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

static void	thinking(t_node *philo)
{
	kinda_usleep(4, philo->tbl);
	print_status(THINKING, philo->index, philo->tbl);
}

static void	eat_and_sleep(t_node *philo)
{
	safe_mutex(philo->l, LOCK, philo->tbl);
	print_status(L_FORK, philo->index, philo->tbl);
	safe_mutex(philo->r, LOCK, philo->tbl);
	print_status(R_FORK, philo->index, philo->tbl);
	print_status(EATING, philo->index, philo->tbl);
	kinda_usleep(philo->tbl->time_eat, philo->tbl);
	set_safe(&philo->p_set, calc_current_ms_time(), &philo->last_eat);
	philo->eated++;
	if (philo->eated == philo->tbl->eat_count)
		return (set_safe(&philo->m_status, FULL, &philo->status));
	safe_mutex(philo->l, UNLOCK, philo->tbl);
	safe_mutex(philo->r, UNLOCK, philo->tbl);
	print_status(SLEEPING, philo->index, philo->tbl);
	kinda_usleep(philo->tbl->time_sleep, philo->tbl);
}

static void	*gods_lonely_man(void *a)
{
	t_node	*philo;

	philo = (t_node *)a;
	wait_all(philo->tbl);
	set_safe(&philo->p_set, calc_current_ms_time(), &philo->last_eat);
	increase_long(&philo->tbl->set, &philo->tbl->i);
	safe_mutex(philo->r, LOCK, philo->tbl);
	print_status(R_FORK, philo->index, philo->tbl);
	kinda_usleep(philo->tbl->time_die, philo->tbl);
	safe_mutex(philo->r, UNLOCK, philo->tbl);
	return (NULL);
}

void	*starting_section(void *a)
{
	t_node	*philo;

	philo = (t_node *)a;
	wait_all(philo->tbl);
	set_safe(&philo->p_set, calc_current_ms_time(), &philo->last_eat);
	increase_long(&philo->tbl->set, &philo->tbl->i);
	if (philo->index % 2)
		usleep(420);
	while (checking_flag(&philo->tbl->waiting, &philo->tbl->d_or_a,
			philo->tbl) == ALIVE)
	{
		eat_and_sleep(philo);
		if (checking_flag(&philo->m_status, &philo->status,
				philo->tbl) != ALIVE)
			return (NULL);
		thinking(philo);
	}
	return (NULL);
}

int	invite_philo(t_dining *table)
{
	size_t	i;

	i = 0;
	if (table->philo_nbr == 1)
		safe_thread(&table->philo_node->philo_id, CREATE, table->philo_node,
			&gods_lonely_man);
	else
	{
		while (++i <= table->philo_nbr)
		{
			safe_thread(&table->philo_node->philo_id, CREATE, table->philo_node,
				&starting_section);
			table->philo_node = table->philo_node->next;
		}
	}
	set_safe(&table->waiting, calc_current_ms_time(), &table->begin_time);
	if (pthread_create(&table->owner, NULL, &check_guests, table))
		return (err_mang(3), getting_up(table), 0);
	set_safe(&table->waiting, -1, &table->flag);
	i = 0;
	while (++i <= table->philo_nbr)
	{
		safe_thread(&table->philo_node->philo_id, JOIN, table->philo_node,
			NULL);
		table->philo_node = table->philo_node->next;
	}
	safe_thread(&table->owner, JOIN, table->philo_node, NULL);
	return (1);
}
