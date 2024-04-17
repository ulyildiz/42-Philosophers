/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:34:19 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/04/17 23:32:20 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include <stdlib.h>

void	clean_node(t_dining *table)
{
	size_t	i;
	t_node	*tmp;

	i = 0;
	while (i < table->philo_nbr && table->philo_node)
	{
		if (table->philo_node->r)
			free(table->philo_node->r);
		tmp = table->philo_node->next;
		if (table->philo_node)
			free(table->philo_node);
		table->philo_node = tmp;
		i++;
	}
}

void	clean_mutex(t_dining *table)
{
	size_t	i;

	i = 0;
	safe_mutex(&table->print, DESTROY, table);
		// mutexin var olup olmamasını nasıl kontrol ederiz
	safe_mutex(&table->waiting, DESTROY, table);
	safe_mutex(&table->set, DESTROY, table);
	while (i < table->philo_nbr)
	{
		safe_mutex(table->philo_node->r, DESTROY, table);
		table->philo_node = table->philo_node->next;
		i++;
	}
}

void	getting_up(t_dining *table)
{
	clean_mutex(table);
	if (table->philo_node)
		clean_node(table);
	exit(1);
}
