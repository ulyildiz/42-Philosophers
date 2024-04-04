#include "functions.h"
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

void	eating_section(t_node *philo)
{
	pthread_mutex_lock(philo->l);
	print_status(R_FORK, philo->index, &philo->tbl->print);
	pthread_mutex_lock(philo->r);
	print_status(L_FORK, philo->index, &philo->tbl->print);
	print_status(EATING, philo->index, &philo->tbl->print);
	usleep(philo->tbl->time_eat * 1000);
	//printf("%d - %lu- \n", philo->index ,calc_current_ms_time() - philo->last_eat);
	if (philo->eated == philo->tbl->eat_count)
	{
		;
	}
	set_safe(&philo->tbl->set, calc_current_ms_time(), &philo->last_eat);
	pthread_mutex_unlock(philo->l);
	pthread_mutex_unlock(philo->r);
	print_status(SLEEPING, philo->index, &philo->tbl->print);
	usleep(philo->tbl->time_sleep * 1000);
	print_status(THINKING, philo->index, &philo->tbl->print);
	usleep(40); // düşünme için ölçek belirle
}

void	*starting_section(void *a)
{
	t_node			*philo;
	int				i;

	i = 0;
	philo = (t_node *)a;
	wait_all(philo->tbl);
	if (philo->index % 2)
		usleep(42);// az olunca düzelmedi?
	set_safe(&philo->tbl->waiting, calc_current_ms_time(), &philo->last_eat);
	while (philo->tbl->d_or_a)
	{
		eating_section(philo);/*
		if (philo->status == DEAD) // take safe
			philo->tbl->d_or_a = DEAD;*/
		// thinking_section(philo);
	}
	return (NULL);
}

int	invite_philo(t_dining *table)
{
	int	i;

	i = -1;
	safe_thread(&table->owner, CREATE, );
	while (++i < table->philo_nbr)
	{
		if (pthread_create(&table->philo_node->philo_id, NULL,
				&starting_section, table->philo_node))
			return (err_mang(3), getting_up(table), 0);
		table->philo_node = table->philo_node->next;
	}
	set_safe(&table->waiting, -1, &table->eat_count);
	i = -1;
	while (++i < table->philo_nbr)
	{
		pthread_join(table->philo_node->philo_id, NULL);
		table->philo_node = table->philo_node->next;
	}
	pthread_join(table->owner, NULL);
	return (1);
}
