CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread #-fsanitize=thread -g
SRC = philo.c philo_utils.c philosophers.c ft_atoi.c

OBJ = $(SRC:.c=.o)

NAME = philo

all : $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJ)


fclean: clean
	rm -f $(NAME)

re: fclean all


.PHONY: all clean fclean re