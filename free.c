/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:34:19 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/04/17 14:27:46 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include <stdlib.h>

void	clean_node(t_dining *table)
{
	size_t	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		if (table->philo_node)
			free(table->philo_node);
		if (table->philo_node->r)
			free(table->philo_node->r);
		table->philo_node = table->philo_node->next;
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
	if (table->philo_node)
		clean_node(table);
	exit(1);
}
