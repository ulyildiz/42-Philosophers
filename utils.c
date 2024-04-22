/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:51:20 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/04/22 11:51:20 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include <stdlib.h>
#include <sys/time.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = -1;
	while (s[++i])
		;
	return (i);
}

size_t	calc_current_ms_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec * 0.001);
}

size_t	ft_patoi(const char *s)
{
	size_t	res;
	int		i;

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
	void	*allc;
	size_t	i;

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
		return (err_mang(1), NULL);
	t->index = i;
	t->eated = 0;
	t->r = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
	if (!t->r)
		return (free(t), err_mang(1), NULL);
	if (pthread_mutex_init(t->r, NULL))
		return (err_mang(2), free(t->r), free(t), NULL);
	if (pthread_mutex_init(&t->p_set, NULL))
		return (err_mang(2), pthread_mutex_destroy(t->r), free(t->r), free(t),
			NULL);
	if (pthread_mutex_init(&t->m_status, NULL))
		return (err_mang(2), pthread_mutex_destroy(&t->p_set),
			pthread_mutex_destroy(t->r), free(t->r), free(t), NULL);
	t->next = t;
	t->prev = t;
	return (t);
}
