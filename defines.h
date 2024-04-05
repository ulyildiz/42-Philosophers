/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 22:37:55 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/04/05 10:41:41 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include <pthread.h>

typedef enum s_flags
{
	DEAD,
	ALIVE,
	EATING,
	THINKING,
	SLEEPING,
	R_FORK,
	L_FORK,
	LOCK,
	UNLOCK,
	CREATE,
	DESTROY,
	INIT,
	JOIN,
	FULL
}			t_flags;

typedef struct s_node
{
	pthread_t		philo_id;
	pthread_mutex_t	*r;
	pthread_mutex_t	*l;
	size_t			born_time;
	size_t			last_eat;
	size_t			eated;
	int				index;
	size_t			status;
	struct s_node	*next;
	struct s_node	*prev;
	struct s_dining	*tbl;
}					t_node;

typedef struct s_dining
{
	int				philo_nbr;
	int				time_eat;
	int				time_die;
	int				time_sleep;
	size_t			flag;
	size_t			eat_count;
	size_t			d_or_a;
	size_t			begin_time;
	pthread_t		owner;
	t_node			*philo_node;
	pthread_mutex_t	print;
	pthread_mutex_t	waiting;
	pthread_mutex_t	set;
	pthread_mutex_t	status;
}					t_dining;

#endif