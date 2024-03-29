NAME = philo
CC = cc -Wall -Wextra -Werror -g
SOURCE = check.c \
		free_error.c \
		loop.c \
		main.c \
		utils.c
OBJ = $(SOURCE:.c=.o)


$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)
all : $(NAME)

.c.o:
	$(CC) -c -o $@ $<

clean:
	@rm -rf *.o
fclean: clean
	@rm -rf $(NAME)
re: fclean all

.PHONY: re fclean clean all