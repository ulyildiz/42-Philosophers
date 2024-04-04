#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "defines.h"

// free_error
void	philos_gone(t_node *philos);
void	getting_up(t_dining *table);
void	err_mang(int flag);

// check
void	*check_guests(void *a);
int		arg_check(int argc, char *argv[]);

int		invite_philo(t_dining *table);
void	print_status(t_flags status, int i, pthread_mutex_t *print);

// utils
int		ft_patoi(const char *s);
t_node	*birth(int i);
void	*ft_calloc(size_t count, size_t nbyte);
size_t	ft_strlen(const char *s);
size_t	calc_current_ms_time(void);

// shit
void	wait_all(t_dining *table);
void	set_safe(pthread_mutex_t *mtx, size_t value, size_t *dst);
int		checking_flag(pthread_mutex_t *mtx, size_t *flag);

#endif