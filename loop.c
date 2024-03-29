#include "functions.h"

int	invite_philo(t_dining *table)
{
	//thread başlat;
	t_node	*tmp;

	tmp = table->philo_node->next;
	while (tmp)
	{
		//timelar
		if(pthread_create(&tmp->philo_id, NULL, , table))
			return (/*free*/ 0);
		tmp = tmp->next;
	}
	while()
	{

	}
	return (1);
}

/*loop fonksiyonların*/


