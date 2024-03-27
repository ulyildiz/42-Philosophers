/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 22:37:55 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/03/27 09:26:30 by ulyildiz         ###   ########.fr       */
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
}	t_flags;

typedef struct s_node
{
	pthread_t		philo_id;
	pthread_mutex_t	*r;
	pthread_mutex_t	*l;
	
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_dining
{
	int			philo_nbr;
	int			time_eat;
	int			time_die;
	int			time_sleep;
	int			eat_count;
	u_int16_t	d_or_a;
	t_node		*philo_node;
	
}	t_dining;

#endif