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

void	*check_guests(void *a)
{
	t_dining	*table;
	t_node		*tmp;

	table = (t_dining *)a;
	tmp = table->philo_node;
	while (1)
	{
		if (tmp->status == DEAD)
		{
			printf("%d. philosopher was dead\n", tmp->index);
			getting_up(table);
		}
		tmp = tmp->next;
		if (!tmp)
			tmp = table->philo_node;
	}
}
