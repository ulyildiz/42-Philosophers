/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:34:29 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/04/17 23:05:11 by ulyildiz         ###   ########.fr       */
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
			return (0);
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
	table->philo_nbr = ft_patoi(argv[1]);
	if (table->philo_nbr == 0)
		return (err_mang(0), 0);
	table->time_die = ft_patoi(argv[2]);
	table->time_eat = ft_patoi(argv[3]);
	table->time_sleep = ft_patoi(argv[4]);
	table->i = 0;
	if (argc == 6)
		table->eat_count = ft_patoi(argv[5]);
	else
		table->eat_count = -1;
	table->flag = 0;
	table->d_or_a = ALIVE;
	table->philo_node = NULL;
	if (!init_node(table))
		return (err_mang(1), getting_up(table), 0);
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
	invite_philo(&table);
	getting_up(&table);
	return (0);
}
