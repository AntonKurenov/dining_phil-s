GREEN = \033[32m
YELLOW = \033[0;33m
NO_COLOR = \x1b[0m
RED = \x1b[31;01m

NAME = philo_one
OBJS = $(SRCS:.c=.o)
# CFLAGS = -Wall -Wextra -Werror

SRCS = philo_one.c \
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
