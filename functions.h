#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "defines.h"

// free_error
void	philos_gone(t_node *philos);
void	getting_up(t_dining *table);

// check
void	*check_guests(void *a);
int		arg_check(int argc, char *argv[]);

int	invite_philo(t_dining *table);

// utils
int ft_patoi(const char *s);
t_node	*birth(int i);
void	*ft_calloc(size_t count, size_t nbyte);
size_t	ft_strlen(const char *s);
size_t	calc_current_time(void);

#endif