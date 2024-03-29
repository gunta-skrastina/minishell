# _*_ MakeFile _*_

CC = gcc
READLINE= -I $(HOME)/goinfre/.brew/opt/readline/include/ -L $(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline
CFLAGS = -Wextra -Wall -Werror
LIBFT = libft.a
NAME = minishell

SRCS = main.c utils.c replace_env.c signals.c env.c env_list_utils.c pwd.c unset.c \
	export.c cd.c error.c split_env.c execute.c parse.c cmd_list_utils.c echo.c exit.c \
	parse_utils.c add_inout.c lim_utils.c parse_inout.c pipe.c pipe_utils.c syntax.c \
	add_inout_utils.c execute_utils.c export_utils.c

OBJS = $(SRCS:.c=.o)

%.o:	%.c
	$(CC) -c -Wextra -Wall -Werror -o $@ $^

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C libft
	cp libft/$(LIBFT) $(LIBFT)


$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINE) -o $(NAME)

clean:
	rm -f $(OBJS) 
	rm -rf *.dSYM
	make clean -C libft

fclean: clean
	rm -f $(NAME) $(LIBFT)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re