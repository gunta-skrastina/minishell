# _*_ MakeFile _*_

CC = gcc
CFLAGS = -Wextra -Wall -Werror

LIBFT = libft.a
NAME = minishell

SRCS = main.c

OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C libft
	cp libft/$(LIBFT) $(LIBFT)


$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LIBFT) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS) 
	rm -rf *.dSYM
	make clean -C libft

fclean: clean
	rm -f $(NAME) $(LIBFT)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re