# _*_ MakeFile _*_

CC = gcc
CFLAGS = -Wextra -Wall -Werror -lreadline
LIBFT = libft.a
NAME = minishell

SRCS = main.c utils.c replace_env.c signals.c env.c env_list_utils.c

OBJS = $(SRCS:.c=.o)

%.o:	%.c
	$(CC) -c -Wextra -Wall -Werror -o $@ $^

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C libft
	cp libft/$(LIBFT) $(LIBFT)


$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

clean:
	rm -f $(OBJS) 
	rm -rf *.dSYM
	make clean -C libft

fclean: clean
	rm -f $(NAME) $(LIBFT)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re