
static int	check_lim(char *ar, char sign, int i)
{
	static char	*int_max = "2147483647";
//	static char	*int_min = "2147483648";

	if (sign == '+')
	{
		if (int_max[i] == ar[i])
		{
			if (!check_lim(ar, sign, ++i))
				return (0);
		}
		else if (int_max[i] < ar[i])
			return (0);
	}
	/*else
	{
		if (int_min[i] == ar[i])
		{
			if (!check_lim(ar, sign, ++i))
				return (0);
		}
		else if (int_min[i] < ar[i])
			return (0);
	}*/
	return (1);
}

static int	set_check(char *ar)
{
	char	sign;
	int		len;

	sign = '+';
	/*if (*ar == '-')
	{
		ar++;
		sign = '-';
	}*/
	while (*ar == '0')
		ar++;
	len = ft_strlen(ar);
	if (len > 10)
		return (0);
	else if (len < 10)
		return (1);
	else if (!check_lim(ar, sign, 0))
		return (0);
	return (1);
}

static int	numeric_check(char *argv[])
{
	int	i;
	int	j;

	i = 0;
	while (argv[i])
	{
		j = -1;
		while (argv[i][++j])
			if (!("0" <= argv[i][j] && argv[i][j] <= "9"))
				return (0);
		i++;
	}
	return (1);
}

int	arg_check(int argc, char *argv[])
{
	int i;

	if (argc < 5 || 6 < argc)
		return (0);
	i = 1;
	while (argv[i])
	{
		if (!numeric_check(argv[i]))
			return (0);
		else if (!set_check(argv[i]))
			return (0);
		i++;
	}
	return (1);
}