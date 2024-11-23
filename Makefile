NAME    = philo
CC      = cc -g

CFLAGS  = -Wall -Wextra -Werror -g #-fsanitize=thread

SRCS    = main.c \
					$(addprefix scrs/, check_input.c exit.c ft_atoi.c init_data.c output.c routine.c routine_utils.c get_time.c end_philo.c philo.c)\

OBJS    = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SILENT:
