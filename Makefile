NAME    = philo
CC      = cc -g
LDLIBS  = -lreadline
CFLAGS  = -Wall -Wextra -Werror -g #-fsanitize=address

SRCS    = main.c \
					$(addprefix scrs/, check_input.c exit.c ft_atoi.c init_data.c mutex.c output.c routine.c get_time.c)\

OBJS    = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDLIBS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SILENT:
