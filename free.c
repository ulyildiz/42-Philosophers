/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:34:19 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/04/18 18:18:28 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include <stdlib.h>
#include <errno.h>

void	destroy_philo_mutexes(t_node *philo)
{
	if (pthread_mutex_destroy(&philo->p_set) == EBUSY)
	{
		pthread_mutex_unlock(&philo->p_set);
		pthread_mutex_destroy(&philo->p_set);
	}
	if (pthread_mutex_destroy(&philo->m_status) == EBUSY)
	{
		pthread_mutex_unlock(&philo->m_status);
		pthread_mutex_destroy(&philo->m_status);
	}
	if (pthread_mutex_destroy(philo->r) == EBUSY)
	{
		pthread_mutex_unlock(philo->r);
		pthread_mutex_destroy(philo->r);
	}
}

void	clean_node(t_dining *table, size_t philo_num)
{
	size_t	i;
	t_node	*tmp;

	i = 0;
	while (i < philo_num)
	{
		destroy_philo_mutexes(table->philo_node);
		if (table->philo_node->r)
			free(table->philo_node->r);
		tmp = table->philo_node->next;
		if (table->philo_node)
			free(table->philo_node);
		table->philo_node = tmp;
		i++;
	}
}

void	destroy_table_mutexes(t_dining *table)
{
	if (pthread_mutex_destroy(&table->print) == EBUSY)
	{
		pthread_mutex_unlock(&table->print);
		pthread_mutex_destroy(&table->print);
	}
	if (pthread_mutex_destroy(&table->set) == EBUSY)
	{
		pthread_mutex_unlock(&table->set);
		pthread_mutex_destroy(&table->set);
	}
	if (pthread_mutex_destroy(&table->waiting) == EBUSY)
	{
		pthread_mutex_unlock(&table->waiting);
		pthread_mutex_destroy(&table->waiting);
	}
}

void	getting_up(t_dining *table)
{
	clean_node(table, table->philo_nbr);
	destroy_table_mutexes(table);
}
