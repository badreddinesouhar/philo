CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -fsanitize=thread
SRC = philo.c philo_utils.c philosophers.c

OBJ = $(SRC:.c=.o)

NAME = philo
LIBFT = lib/libft.a

all : $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C lib

clean:
	make clean -C lib
	rm -f $(OBJ)


fclean: clean
	make fclean -C lib
	rm -f $(NAME)

re: fclean all


.PHONY: all clean fclean re