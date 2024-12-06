NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS =  philosophers.c \
		utils.c \
		errors.c \
		checks.c \
		lifecircle.c \
		initialization.c \

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) philosophers.h
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus