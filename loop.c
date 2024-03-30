#include "functions.h"
#include <unistd.h>

void	*sleeping_section(void *a);
	/*loop fonksiyonların*/
void *thinking_section(void *a)
{
	t_node	*philo;

	philo = (t_node *)a;
	philo->status = THINKING;
	//	usleep(1000);
	write(2, "t", 1);
	philo->status = DEAD;
	sleeping_section(philo);
	return (NULL);
}

void	*eating_section(void *a)
{
	t_node	*philo;

	philo = (t_node *)a;
	philo->status = EATING;
	//	usleep(100);
	write(2, "e", 1);
	thinking_section(philo);
	return (NULL);
}

void	*sleeping_section(void *a)
{
	t_node	*philo;

	philo = (t_node *)a;
	philo->status = SLEEPING;
	//	usleep(1000);
	write(2, "s", 1);
	eating_section(philo);
	return (NULL);
}

int	invite_philo(t_dining *table)
{
	t_node	*tmp;

	// thread başlat;
	if (pthread_create(&table->owner, NULL, &check_guests, table)
		&& pthread_join(table->owner, NULL))
		return (getting_up(table), 0);
	tmp = table->philo_node;
	sleeping_section(tmp);
	/*while (tmp)
	{
		// timelar
		if (pthread_create(&tmp->philo_id, NULL, &sleeping_section, tmp)
			&& pthread_join(tmp->philo_id, NULL))
			return (getting_up(table), 0);
		tmp = tmp->next;
	}*/
	write(2, "a", 1);
	return (1);
}
