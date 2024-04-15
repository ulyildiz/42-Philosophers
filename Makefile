NAME = philo
CC = cc -Wall -Wextra -Werror -g
SOURCE = check.c \
		free.c \
		loop.c \
		main.c \
		print.c \
		safety_functions.c \
		shit.c \
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