#include "functions.h"
#include <unistd.h>

/*loop fonksiyonların*/
void	sleeping_section(t_node *philo)
{
	print_status(SLEEPING, philo->index, &philo->tbl->print);
	usleep(philo->tbl->time_sleep * 1000); // sleeping_time;
	
}

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
	usleep(philo->tbl->time_eat * 1000);

}

void	*starting_section(void *a)
{
	t_dining	*table;

	table = (t_dining *)a;
	while (table->d_or_a)
	{
		eating_section(table->philo_node);
		thinking_section(table->philo_node);
		sleeping_section(table->philo_node);
	}
	return (NULL);
}

int	invite_philo(t_dining *table)
{
	t_node	*tmp;

	// thread başlat;
	if (pthread_create(&table->owner, NULL, &check_guests, table)
		&& pthread_join(table->owner, NULL))
		return (err_mang(3), 0);
	tmp = table->philo_node;
	table->begin_time = calc_current_ms_time();
	//starting_section(table);
	while (tmp)
	{
		tmp->last_eat = table->begin_time;
		if (pthread_create(&tmp->philo_id, NULL, &starting_section, tmp)
			&& pthread_join(tmp->philo_id, NULL))
			return (err_mang(3), 0);
		tmp = tmp->next;
	}
	return (1);
}
