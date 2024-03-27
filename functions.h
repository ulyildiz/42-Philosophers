#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "defines.h"

// check
int		arg_check(int argc, char *argv[]);

// utils
int		ft_patoi(const char *s);
t_node	*birth(int i);
void	*ft_calloc(size_t count, size_t nbyte);

#endif