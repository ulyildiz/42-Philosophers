#include "functions.h"
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>

static int	init_node(t_dining *table)
{
	t_node	*tmp2;
	t_node	*tmp;
	int		i;

	i = 0;
	tmp2 = (table->philo_node);
	while (++i <= table->philo_nbr)
	{
		tmp = birth(i);
		if (!tmp)
			return (philos_gone(table->philo_node), 0);
		if (!table->philo_node)
			table->philo_node = tmp;
		else
		{
			tmp2 = table->philo_node;
			while(tmp2->next)
				tmp2 = tmp2->next;
			tmp2->next = tmp;
			tmp->prev = tmp2;
		}
		tmp->status = ALIVE;
		tmp->tbl = table;
	}
	return (1);
}

static int	init_table(t_dining *table, int argc, char *argv[])
{
	t_node	*tmp;

	table->philo_nbr = ft_patoi(argv[1]);
	/*if (table->philo_nbr == 1)
		return (0);*/
	table->time_die = ft_patoi(argv[2]);
	table->time_eat = ft_patoi(argv[3]);
	table->time_sleep = ft_patoi(argv[4]);
	if (argc == 6)
		table->eat_count = ft_patoi(argv[5]);
	else
		table->eat_count = 0;
	table->d_or_a = ALIVE;
	table->philo_node = NULL;
	if (!init_node(table))
		return (0);
	tmp = table->philo_node;
	while (tmp != table->philo_node)
	{
		tmp->r = tmp->prev->l;
		tmp = tmp->next;
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_dining	table;
//	t_node *tmp;

	if (!arg_check(argc, argv) || !init_table(&table, argc, argv))
		return (write(2, "c\n", 2), 1);
	
	/*tmp = table.philo_node;
	while (tmp)
	{
		printf("%d\n", tmp->index);
		tmp = tmp->next;
	}*/
	invite_philo(&table);
	/*is_sb_died();*/
	return (0);
}
