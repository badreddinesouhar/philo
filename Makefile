CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
SRC = philo.c

OBJ = $(SRC:.c=.o)

TARGET = philo
LIBFT = lib/libft.a

all : $(TARGET)

$(TARGET): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LIBFT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C lib

clean:
	make clean -C lib
	rm -f $(OBJ)


fclean: clean
	make fclean -C lib
	rm -f $(TARGET)

re: fclean all


.PHONY: all clean fclean re