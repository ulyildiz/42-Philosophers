#include "functions.h"
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

static void	sleeping_section(t_node *philo)
{
	usleep(philo->tbl->time_sleep * 1000);
	print_status(SLEEPING, philo->index, philo->tbl);
}

static void	thinking_section(t_node *philo)
{
	usleep(40); // düşünme için ölçek belirle
	print_status(THINKING, philo->index, philo->tbl);
}

static void	eating_section(t_node *philo)
{
	safe_mutex(philo->l, LOCK, philo->tbl);
	print_status(R_FORK, philo->index, philo->tbl);
	safe_mutex(philo->r, LOCK, philo->tbl);
	print_status(L_FORK, philo->index, philo->tbl);
	//	printf("%d - %lu- \n", philo->index, calc_current_ms_time()
	//		- philo->last_eat);
	if (calc_current_ms_time() - philo->last_eat > philo->tbl->time_die)
		return (set_safe(&philo->tbl->status, DEAD, &philo->status), usleep(3),
			safe_mutex(philo->l, UNLOCK, philo->tbl), safe_mutex(philo->r,
				UNLOCK, philo->tbl));
	usleep(philo->tbl->time_eat * 1000);
	print_status(EATING, philo->index, philo->tbl);
	set_safe(&philo->tbl->set, calc_current_ms_time(), &philo->last_eat);
	philo->eated++;
	safe_mutex(philo->l, UNLOCK, philo->tbl);
	safe_mutex(philo->r, UNLOCK, philo->tbl);
	if (philo->eated == philo->tbl->eat_count)
		return (set_safe(&philo->tbl->status, FULL, &philo->status));
}

void	*starting_section(void *a)
{
	t_node	*philo;
	int		i;

	i = 0;
	philo = (t_node *)a;
	wait_all(philo->tbl);
	if (philo->index % 2)
		usleep(42);
	set_safe(&philo->tbl->waiting, calc_current_ms_time(), &philo->last_eat);
	while (checking_flag(&philo->tbl->waiting, &philo->tbl->d_or_a,
			philo->tbl) == ALIVE)
	{
		eating_section(philo);
		if (philo->status == FULL || philo->status == DEAD)
			return (NULL);
		sleeping_section(philo);
		thinking_section(philo);
	}
	return (NULL);
}

int	invite_philo(t_dining *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		safe_thread(&table->philo_node->philo_id, CREATE, table->philo_node,
			&starting_section);
		table->philo_node = table->philo_node->next;
	}
	if (pthread_create(&table->owner, NULL, &check_guests, table))
		return (err_mang(3), getting_up(table), 0);
	set_safe(&table->waiting, -1, &table->flag);
	i = -1;
	while (++i < table->philo_nbr)
	{
		safe_thread(&table->philo_node->philo_id, JOIN, table->philo_node,
			NULL);
		table->philo_node = table->philo_node->next;
	}
	safe_thread(&table->owner, JOIN, table->philo_node, NULL);
	return (1);
}
