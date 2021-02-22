NAME = philo_two
OBJS = $(SRCS:.c=.o)
# CFLAGS = -Wall -Wextra -Werror

SRCS = philo_two.c \
		simulation.c utils.c \
		prep_for_start.c start_threads.c \

all: $(NAME)

$(NAME): $(OBJS)
	gcc -o $(NAME) -pthread $(OBJS)
	# gcc $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:	fclean $(NAME)

.PHONY:	all clean fclean re
