#include "functions.h"
#include <stdio.h>

static int	check_lim(char *ar, int i)
{
	char	*int_max;

	int_max = "2147483647";
	if (int_max[i] == ar[i])
	{
		if (!check_lim(ar, ++i))
			return (0);
	}
	else if (int_max[i] < ar[i])
		return (0);
	return (1);
}

static int	set_check(char *ar)
{
	int	len;

	while (*ar == '0')
		ar++;
	len = ft_strlen(ar);
	if (len > 10)
		return (0);
	else if (len < 10)
		return (1);
	else if (!check_lim(ar, 0))
		return (0);
	return (1);
}

static int	numeric_check(char *argv)
{
	int	i;

	i = 0;
	if (argv[i] == '+')
		i++;
	while (argv[i])
	{
		if (!('0' <= argv[i] && argv[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	arg_check(int argc, char *argv[])
{
	int	i;

	if (argc < 5 || 6 < argc)
		return (printf("Please enter 5 input. (6th is optional)\n"), 0);
	i = 1;
	while (argv[i])
	{
		if (!numeric_check(argv[i]) && !set_check(argv[i]))
			return (err_mang(0), 0);
		i++;
	}
	return (1);
}

static int	check_dead(t_node *current_philo)
{
	if (checking_flag(&current_philo->m_status, &current_philo->status, current_philo->tbl) == FULL)
		return (0);
	if (calc_current_ms_time() - checking_flag(&current_philo->p_set, &current_philo->last_eat, current_philo->tbl) > current_philo->tbl->time_die)
		return (set_safe(&current_philo->m_status, DEAD, &current_philo->status), 1);
	return (0);
}

void	*check_guests(void *a)
{
	t_dining	*table;
	t_node		*tmp;

	table = (t_dining *)a;
	tmp = table->philo_node;
	while (1)
		if (checking_flag(&table->set, &table->i, table) == table->philo_nbr)
			break ;
	while (1)
	{
		if (check_dead(tmp))
		{
			set_safe(&table->waiting, DEAD, &table->d_or_a);
			print_status(DEAD, tmp->index, table);
			return (NULL);
		}
		tmp = tmp->next;
	}
}
