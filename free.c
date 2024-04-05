#include "functions.h"
#include <stdlib.h>

void	clean_node(t_dining *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		if (table->philo_node)
			free(table->philo_node);
		if (table->philo_node->r) //?
			free(table->philo_node->r);
		table->philo_node = table->philo_node->next;
	}
}

void	clean_mutex(t_dining *table)
{
	int	i;

	i = -1;
	safe_mutex(&table->print, DESTROY, table); // mutexin var olup olmamasını nasıl kontrol ederiz
	safe_mutex(&table->waiting, DESTROY, table);
	safe_mutex(&table->set, DESTROY, table);
	while (++i < table->philo_nbr)
	{
		safe_mutex(table->philo_node->r, DESTROY, table);
		table->philo_node = table->philo_node->next;
	}
}

void	getting_up(t_dining *table)
{
	if (table->philo_node)
		clean_node(table);
	exit(1);
}
