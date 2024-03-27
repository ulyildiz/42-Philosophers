#include "defines.h"
#include <stdlib.h>

int	ft_patoi(const char *s)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (s[i] == ' ' || (9 <= s[i] && s[i] <= 13))
		i++;
	while (s[i] == '0')
		i++;
	while ('0' <= s[i] && s[i] <= '9')
		res = (s[i++] - '0') + res * 10;
	return (res);
}

void	*ft_calloc(size_t count, size_t nbyte)
{
	void		*allc;
	u_int64_t	i;

	i = count * nbyte;
	allc = malloc(i);
	if (!allc)
		return (NULL);
	while (i)
		((char *)allc)[--i] = '\0';
	return (allc);
}

t_node	*birth(int i)
{
	t_node	*t;

	t = (t_node *)ft_calloc(1, sizeof(t_node));
	if (!t)
		return (NULL);
	if (!pthread_mutex_init(t->l, NULL))
		return (NULL); // free(t) ?
	//lock f?
	return (t);
}
