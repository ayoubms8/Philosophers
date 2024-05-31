SRCS := init.c main.c utils.c utils2.c parsin.c

OBJS := $(SRCS:.c=.o)

CC := gcc

CFLAGS := -Wall -Wextra -Werror

all: philo

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

philo: $(OBJS) philo.h
	$(CC) $(CFLAGS) $(OBJS) -o philo

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f philo

re: fclean all

.PHONY: all clean fclean re