/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:34:29 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/04/17 14:19:37 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	init_node(t_dining *table)
{
	t_node	*tmp;
	size_t	i;

	i = 0;
	while (++i <= table->philo_nbr)
	{
		tmp = birth(i);
		if (!tmp)
			return (clean_node(table), 0);
		if (!table->philo_node)
			table->philo_node = tmp;
		else
		{
			table->philo_node->prev->next = tmp;
			tmp->prev = table->philo_node->prev;
			tmp->next = table->philo_node;
			table->philo_node->prev = tmp;
		}
		tmp->status = ALIVE;
		tmp->tbl = table;
	}
	return (1);
}

static void	forks(t_dining *table)
{
	t_node	*tmp;

	tmp = table->philo_node->next;
	while (tmp != table->philo_node)
	{
		tmp->l = tmp->prev->r;
		tmp = tmp->next;
	}
	tmp->l = tmp->prev->r;
}

static int	init_table(t_dining *table, int argc, char *argv[])
{
	t_node	*tmp;

	table->philo_nbr = ft_patoi(argv[1]);
	table->time_die = ft_patoi(argv[2]);
	table->time_eat = ft_patoi(argv[3]);
	table->time_sleep = ft_patoi(argv[4]);
	table->i = 0;
	if (argc == 6)
		table->eat_count = ft_patoi(argv[5]);
	else
		table->eat_count = -1;
	table->flag = 0;
	table->philo_node = NULL;
	if (!init_node(table))
		return (0);
	safe_mutex(&table->print, INIT, table);
	safe_mutex(&table->set, INIT, table);
	safe_mutex(&table->waiting, INIT, table);
	forks(table);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_dining	table;

	if (!arg_check(argc, argv) || !init_table(&table, argc, argv))
		return (1);
	table.d_or_a = ALIVE;
	if (!invite_philo(&table))
		getting_up(&table);
	return (0);
}

	/*while (table.philo_node)
	{
		printf("%d. left_f = %p, right_f = %p\n", table.philo_node->index,
			table.philo_node->l, table.philo_node->r);
		table.philo_node = table.philo_node->next;
	}*/