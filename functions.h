#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "defines.h"

// free_error
void	clean_node(t_dining *table);
void	getting_up(t_dining *table);
void	clean_mutex(t_dining *table);
void	err_mang(int flag);

// check
void	*check_guests(void *a);
int		arg_check(int argc, char *argv[]);

int		invite_philo(t_dining *table);
void	print_status(t_flags status, int i, t_dining *tbl);

// utils
size_t	ft_patoi(const char *s);
t_node	*birth(int i);
void	*ft_calloc(size_t count, size_t nbyte);
size_t	ft_strlen(const char *s);
size_t	calc_current_ms_time(void);

// shit
void	wait_all(t_dining *table);
void	set_safe(pthread_mutex_t *mtx, size_t value, size_t *dst);
size_t		checking_flag(pthread_mutex_t *mtx, size_t *flag, t_dining *tbl);

// safe
void	safe_mutex(pthread_mutex_t *mtx, t_flags flag, t_dining *tbl);
void	safe_thread(pthread_t *thread, t_flags flag, t_node *philo,
			void *(*func)(void *));
#endif