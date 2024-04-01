#include "functions.h"
#include <unistd.h>

/*loop fonksiyonların*/
void	thinking_section(t_node *philo)
{
	print_status(THINKING, philo->index, &philo->tbl->print);
	// waiting_time;
	
}

void	eating_section(t_node *philo)
{
	pthread_mutex_lock(philo->l);
	print_status(R_FORK, philo->index, &philo->tbl->print);
	pthread_mutex_lock(philo->r);
	print_status(L_FORK, philo->index, &philo->tbl->print);
	print_status(EATING, philo->index, &philo->tbl->print);
	
}

void	sleeping_section(t_node *philo)
{
	print_status(SLEEPING, philo->index, &philo->tbl->print);
	// sleeping_time;
	
}

void	*starting_section(void *a)
{
	t_node	*philo;

	philo = (t_node *)a;
	// if()
}

int	invite_philo(t_dining *table)
{
	t_node	*tmp;

	// thread başlat;
	if (pthread_create(&table->owner, NULL, &check_guests, table)
		&& pthread_join(table->owner, NULL))
		return (err_mang(3), 0);
	tmp = table->philo_node;
	/*while (tmp)
	{
		// timelar
		if (pthread_create(&tmp->philo_id, NULL, &starting_section, tmp)
			&& pthread_join(tmp->philo_id, NULL))
			return (err_mang(3), 0);
		tmp = tmp->next;
	}*/
	return (1);
}
