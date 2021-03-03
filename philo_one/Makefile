NAME = philo_one
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror

SRCS = philo_one.c utils.c \
		initialization.c start_threads.c \
		simulation.c

all: $(NAME)

$(NAME): $(OBJS)
	gcc $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:	fclean $(NAME)

.PHONY:	all clean fclean re
