#include "defines.h"
#include <stdlib.h>

void	philos_gone(t_node *philos)
{
	t_node	*tmp;

	tmp = philos;
	while (philos)
	{
		if (tmp->l)
		{
			pthread_mutex_destroy(tmp->l);
			free(tmp->l);
		}
		tmp = philos->next;
		free(philos);
		philos = tmp;
	}
}

void	getting_up(t_dining *table)
{
	if (table->philo_node)
		philos_gone(table->philo_node);
	//if (table->print) //?
	//	pthread_mutex_destroy(&table->print);
	exit(1);
}
