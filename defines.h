/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 22:37:55 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/04/01 15:54:46 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include <pthread.h>

typedef enum e_flags
{
	DEAD,
	ALIVE,
	EATING,
	THINKING,
	SLEEPING,
	R_FORK,
	L_FORK,
}	t_flags;

typedef struct s_node
{
	pthread_t		philo_id;
	pthread_mutex_t	*r;
	pthread_mutex_t	*l;
	size_t			born_time;
	size_t			last_eat;
	int				index;
	short int		status;
	struct s_node	*next;
	struct s_node	*prev;
	struct s_dining	*tbl;
}	t_node;

typedef struct s_dining
{
	int				philo_nbr;
	int				time_eat;
	int				time_die;
	int				time_sleep;
	int				eat_count;
	short int		d_or_a;
	size_t			begin_time;
	pthread_t		owner;
	pthread_mutex_t	print;
	t_node			*philo_node;
	
}	t_dining;

#endif