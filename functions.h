/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyildiz <ulyildiz@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:34:21 by ulyildiz          #+#    #+#             */
/*   Updated: 2024/04/17 23:06:15 by ulyildiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "defines.h"

// free_error
void	clean_node(t_dining *table, size_t philo_num);
void	getting_up(t_dining *table);
void	err_mang(int flag);
void	destroy_philo_mutexes(t_node *philo);
void	destroy_table_mutexes(t_dining *table);

// check
void	*check_guests(void *a);
int		arg_check(int argc, char *argv[]);

//loop
int		invite_philo(t_dining *table);
void	print_status(t_flags status, int i, t_dining *tbl);

// utils
size_t	ft_patoi(const char *s);
t_node	*birth(int i);
void	*ft_calloc(size_t count, size_t nbyte);
size_t	ft_strlen(const char *s);
size_t	calc_current_ms_time(void);

// utils2
int		wait_all(t_dining *table);
void	set_safe(pthread_mutex_t *mtx, size_t value, size_t *dst);
size_t	checking_flag(pthread_mutex_t *mtx, size_t *flag);
void	kinda_usleep(size_t ms, t_dining *table);
void	increase_long(pthread_mutex_t *mutex, size_t *value);

#endif