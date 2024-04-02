#include "functions.h"
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

/*loop fonksiyonların*/
/*void	sleeping_section(t_node *philo)
{
	print_status(SLEEPING, philo->index, &philo->tbl->print);
	usleep(philo->tbl->time_sleep * 1000); // sleeping_time;
}

void	thinking_section(t_node *philo)
{
	print_status(THINKING, philo->index, &philo->tbl->print);
	usleep((philo->tbl->time_eat + philo->tbl->time_sleep) / 2 *1000);// waiting_time;
}*/

void	eating_section(t_node *philo)
{
	pthread_mutex_lock(philo->l);
	print_status(R_FORK, philo->index, &philo->tbl->print);
	pthread_mutex_lock(philo->r);
	print_status(L_FORK, philo->index, &philo->tbl->print);
	print_status(EATING, philo->index, &philo->tbl->print);
	usleep(philo->tbl->time_eat * 1000);
	pthread_mutex_unlock(philo->l);
	pthread_mutex_unlock(philo->r);
	set_safe(&philo->tbl->set, calc_current_ms_time(), &philo->last_eat);//set last_eat
	if (philo->eated == philo->tbl->eat_count)
	{
		;
	}
	print_status(SLEEPING, philo->index, &philo->tbl->print);
	usleep(philo->tbl->time_sleep * 1000);
	print_status(THINKING, philo->index, &philo->tbl->print);
	//usleep(420);
}

void	*starting_section(void *a)
{
	t_node	*philo;

	philo = (t_node *)a;
	wait_all(philo->tbl);
	if (philo->index % 2 == 0)
		usleep(42);
	while (philo->tbl->d_or_a)
	{
		eating_section(philo);
		//sleeping_section(philo);
		//thinking_section(philo);
	}
	return (NULL);
}

int	invite_philo(t_dining *table)
{
	int		i;
	t_node	*tmp;

	// thread başlat;
	i = -1;
	if (pthread_create(&table->owner, NULL, &check_guests, table)
		&& pthread_join(table->owner, NULL))
		return (err_mang(3), getting_up(table), 0);
	tmp = table->philo_node;
	table->begin_time = calc_current_ms_time();
	while (++i < table->philo_nbr)
	{
		tmp->last_eat = table->begin_time;
		if (pthread_create(&tmp->philo_id, NULL, &starting_section, tmp)
			&& pthread_join(tmp->philo_id, NULL))
			return (err_mang(3), getting_up(table), 0);
		tmp = tmp->next;
	}
	set_safe(&table->waiting, 0, &table->eat_count);
	return (1);
}
