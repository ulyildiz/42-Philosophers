#include "functions.h"
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

static void	sleeping_section(t_node *philo)
{
	usleep(philo->tbl->time_sleep * 1000);
	if (checking_flag(&philo->tbl->waiting, &philo->tbl->d_or_a,
			philo->tbl) != ALIVE)
			return ;
	print_status(SLEEPING, philo->index, philo->tbl);
}

static void	thinking_section(t_node *philo)
{
	usleep(40);
	if (checking_flag(&philo->tbl->waiting, &philo->tbl->d_or_a,
		philo->tbl) != ALIVE)
		return ;
	print_status(THINKING, philo->index, philo->tbl);
}

static void	eating_section(t_node *philo)
{
	safe_mutex(philo->l, LOCK, philo->tbl);
	print_status(L_FORK, philo->index, philo->tbl);
	safe_mutex(philo->r, LOCK, philo->tbl);
	print_status(R_FORK, philo->index, philo->tbl);
	set_safe(&philo->p_set, calc_current_ms_time(), &philo->last_eat);
	print_status(EATING, philo->index, philo->tbl);
	usleep(philo->tbl->time_eat * 1000);
	philo->eated++;
	if (philo->eated == philo->tbl->eat_count)
		return (set_safe(&philo->m_status, FULL, &philo->status));
	safe_mutex(philo->l, UNLOCK, philo->tbl);
	safe_mutex(philo->r, UNLOCK, philo->tbl);
}
void	increase_long(pthread_mutex_t *mutex, size_t *value)
{	
	safe_mutex(mutex, LOCK, NULL);
	(*value)++;
	safe_mutex(mutex, UNLOCK, NULL);
}
void	*starting_section(void *a)
{
	t_node	*philo;

	philo = (t_node *)a;
	wait_all(philo->tbl);
	set_safe(&philo->p_set, calc_current_ms_time(), &philo->last_eat);
	increase_long(&philo->tbl->set, &philo->tbl->i);
	if (philo->index % 2)
		usleep(42);
	while (checking_flag(&philo->tbl->waiting, &philo->tbl->d_or_a,
			philo->tbl) == ALIVE)
	{
		eating_section(philo);
		if (checking_flag(&philo->m_status, &philo->status, philo->tbl) == FULL)
			return (NULL);
		sleeping_section(philo);
		thinking_section(philo);
	}
	return (NULL);
}

int	invite_philo(t_dining *table)
{
	size_t	i;

	i = 0;
	while (++i <= table->philo_nbr)
	{
		safe_thread(&table->philo_node->philo_id, CREATE, table->philo_node,
			&starting_section);
		table->philo_node = table->philo_node->next;
	}
	if (pthread_create(&table->owner, NULL, &check_guests, table))
		return (err_mang(3), getting_up(table), 0);
	set_safe(&table->waiting, calc_current_ms_time(), &table->begin_time);
	set_safe(&table->waiting, -1, &table->flag);
	i = 0;
	while (++i <= table->philo_nbr)
	{
		safe_thread(&table->philo_node->philo_id, JOIN, table->philo_node,
			NULL);
		table->philo_node = table->philo_node->next;
	}
	safe_thread(&table->owner, JOIN, table->philo_node, NULL);
	return (1);
}
