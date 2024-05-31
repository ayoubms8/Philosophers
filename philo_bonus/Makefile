SRCS := main_bonus.c init_bonus.c utils_bonus.c utils2_bonus.c
OBJS := $(SRCS:.c=.o)
NAME := philo_bonus
CC := gcc
CFLAGS := -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OBJS) philo_bonus.h
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o : %.c philo_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all