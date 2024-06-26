/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:51:02 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/04/22 11:51:02 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

static int	init_node(t_dining *table)
{
	t_node	*tmp;
	size_t	i;

	i = 0;
	while (++i <= table->philo_nbr)
	{
		tmp = birth(i);
		if (!tmp)
			return (clean_node(table, i), 0);
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

static int	table_mutexes(t_dining *table)
{
	if (pthread_mutex_init(&table->print, NULL))
		return (0);
	if (pthread_mutex_init(&table->set, NULL))
		return (pthread_mutex_destroy(&table->print), 0);
	if (pthread_mutex_init(&table->waiting, NULL))
		return (pthread_mutex_destroy(&table->print),
			pthread_mutex_destroy(&table->set), 0);
	return (1);
}

static int	init_table(t_dining *table, int argc, char *argv[])
{
	table->philo_nbr = ft_patoi(argv[1]);
	if (table->philo_nbr == 0)
		return (0);
	table->time_die = ft_patoi(argv[2]);
	table->time_eat = ft_patoi(argv[3]);
	table->time_sleep = ft_patoi(argv[4]);
	table->i = 0;
	if (argc == 6)
		table->eat_count = ft_patoi(argv[5]);
	else
		table->eat_count = -1;
	table->detached = 0;
	table->flag = 0;
	table->d_or_a = ALIVE;
	table->philo_node = NULL;
	if (!table_mutexes(table) || !init_node(table))
		return (err_mang(1), 0);
	forks(table);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_dining	table;
	size_t		check;

	if (!arg_check(argc, argv) || !init_table(&table, argc, argv))
		return (1);
	check = invite_philo(&table);
	if (check != 0)
	{
		while (checking_flag(&table.set, &table.detached) != check)
			;
		err_mang(3);
	}
	getting_up(&table);
	return (0);
}
