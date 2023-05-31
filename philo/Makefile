
NAME = philo

CFILES = main.c input.c philostuffer.c time.c simulation.c

OFILES = $(CFILES:.c=.o)

CFLAGS = -Wall -Werror -Wextra -c

all: $(NAME)

$(OFILES): $(CFILES)
	cc $(CFLAGS) $^

$(NAME): $(OFILES)
	cc -o $(NAME) $(OFILES)

clean:
	-rm -f $(OFILES)

fclean: clean
	-rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
