#include "defines.h"
#include <stdlib.h>

void	philos_gone(t_node *philos)
{
	t_node	*tmp;

	if (!philos)
		return ;
	tmp = philos->next;
	while (tmp != philos)
	{
		if (tmp->l)
		{
			pthread_mutex_destroy(tmp->l);
			free(tmp->l);
		}
		tmp = tmp->next;
		free(tmp->prev);
	}
	if (tmp == philos)
	{
		pthread_mutex_destroy(tmp->l);
		free(tmp->l);
	}
	free(tmp);
}

void	getting_up(t_dining *table)
{
	if (table->philo_node)
		philos_gone(table->philo_node);
	exit(1);
}
